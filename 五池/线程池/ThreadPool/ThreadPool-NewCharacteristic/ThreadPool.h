#pragma once
#include <vector>
#include<queue>
#include<mutex>
#include<atomic>
#include <iostream>
#include<condition_variable>
#include<memory>
#include <functional>
#include<typeinfo>
#include<unordered_map>
#include<thread>
#include<future>
#ifndef THREAD_POOL_H
#define THREAD_POOL_H


const int TASK_MAX_THRESHOLD = 2; // INT_MAX;
const int THREAD_MAX_THRESHOLD = 20;
const int THREAD_MAX_IDLE_TIME = 10; //单位:  s

// 线程池支持的模式.
enum class PoolMode
{
	MODE_FIXED,  // 固定数量的线程
	MODE_CACHED, // 动态增长的线程
};

// 线程类型. 
class Thread
{
public:
	using ThreadFunc = std::function<void(int)>;

	Thread(ThreadFunc func)
		:func_(func)
		, threadId_(generateId_++)
	{
	}

	~Thread() = default;

	// 启动线程.
	void start()
	{
		// 创建一个线程来执行一个线程函数.
		std::thread t(func_, threadId_);
		t.detach();		//设置分离线程.
	}

	// 获取线程 id.
	int getId() const
	{
		return threadId_;
	}
private:
	ThreadFunc func_;
	static int generateId_;
	int threadId_;
};
int Thread::generateId_ = 0;

// 
class ThreadPool
{
public:
	ThreadPool()
		:initThreadSize_(0)
		, threadSizeThreshold_(THREAD_MAX_THRESHOLD)
		, curThreadSize_(0)
		, idleThreadSize_(0)
		, taskSize_(0)
		, taskQueMaxThreshold_(TASK_MAX_THRESHOLD)
		, poolMode_(PoolMode::MODE_FIXED)
		, isPoolRunning_(false)
	{}

	~ThreadPool()
	{
		isPoolRunning_ = false;

		//notEmpty_.notify_all();

		// 等待线程池里的所有线程返回,  两种状态: 阻塞 & 执行任务中. 解决死锁问题. 
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		notEmpty_.notify_all();

		exitCond_.wait(lock, [&]() -> bool {
			return threads_.size() == 0;
			});
	}


	// 设置线程池的工作模式.
	void setMode(PoolMode mode)
	{
		if (checkRunningState())
			return;
		poolMode_ = mode;
	}


	// 设置 task任务队列的上线阀值.
	void setTaskQueMaxThreshHold(int threshold)
	{
		if (checkRunningState())
			return;
		taskQueMaxThreshold_ = threshold;
	}

	// 设置线程池 cached 模式下 线程阈值.
	void setThreadMaxSize(int threshold)
	{
		if (checkRunningState())
			return;
		if (poolMode_ == PoolMode::MODE_CACHED)
			threadSizeThreshold_ = threshold;
	}

	// 给线程池提供任务.
	// 使用可变参模板编程, 让给 submitTask可以接受任意任务
	//和任意数量的参数.
	// pool.submitTask(sum1,10,20);
	// 返回值 future<> 
	template<typename Func, typename... Args> // // 引用折叠. decltype.
	auto submitTask(Func&& func, Args&&... args) -> std::future<decltype(func(args...))>
	{
		// 打包任务 放入任务队列.
		using RType = decltype(func(args...));
		auto task = std::make_shared<std::packaged_task<RType()>>(
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
		);
		std::future<RType> result = task->get_future();

		// 获取锁.
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		// 线程的通信 - 等待任务队列有空余. wait  wait_for  wait_until 
		if (!notFull_.wait_for(lock, std::chrono::seconds(2), [&]() -> bool {
			return taskQue_.size() < taskQueMaxThreshold_;
			}))
		{
			// 如果 notFull_ 等待两秒, 条件依然没有满足. 
			std::cerr << "task queue is full, submit task fail." << std::endl;
			auto task = std::make_shared<std::packaged_task<RType()>>(
				[]() -> RType {return RType();});
			(*task)();
			return task->get_future();
		}

		// 如果有空余, 把任务放入任务队列.
		// using Task = std::function<void()>;
		taskQue_.emplace([task]() {
			// 执行下面任务.
			(*task)();
			});
		taskSize_++;

		// 因为放了任务, 任务队列肯定不为空, 在 notEmpty_ 上进行通知.
		notEmpty_.notify_all();

		// cached 模式下 任务处理紧急, 场景: 小而快的任务,需要根据任务数量和空闲线程数量,判断是否需要创建线程.
		if (poolMode_ == PoolMode::MODE_CACHED &&
			curThreadSize_ < threadSizeThreshold_ &&
			taskSize_ > idleThreadSize_)
		{
			std::cout << "create new Thread.. " << std::endl;
			// 创建新的线程对象.
			std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));

			// 启动线程.
			threads_[threadId]->start();

			// 修改线程相关变量.
			curThreadSize_++;
			idleThreadSize_++;
		}

		// 返回任务的 Result 对象.
		return result;
	}


	// 开启线程池.
	void start(int initThreadNum)
	{
		// 设置线程池的运行状态.
		isPoolRunning_ = true;

		// 记录初始线程个数.
		initThreadSize_ = initThreadNum;
		curThreadSize_ = initThreadNum;

		// 创建线程对象.
		for (int i = 0;i < initThreadSize_; ++i)
		{
			// 创建 thread 线程对象的时候, 把线程函数给 thread 线程对象.
			std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));
			//threads_.emplace_back(std::move(ptr));
		}

		// 启动所有线程.
		for (int i = 0;i < initThreadSize_; ++i)
		{
			threads_[i]->start();
			idleThreadSize_++;
		}

	}

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// 定义线程函数.
	void threadFunc(int threadid)
	{
		auto lastTime = std::chrono::high_resolution_clock().now();
		for (;;)
		{
			Task task;
			// 加锁.
			{
				std::cout << "tid:" << std::this_thread::get_id() << " 尝试获取锁....!" << std::endl;
				std::unique_lock<std::mutex> lock(taskQueMtx_);
				std::cout << "tid:" << std::this_thread::get_id() << " 获取锁!" << std::endl;

				// cached 模式下, 有可能创建了很多线程，但是空闲时间超过 60s, 应该把多余的线程结束并且回收掉,
				// 超过 (initThreadSize_ 数量的线程要进行回收),
				// 当前时间 - 上一次线程执行的时间 > 60

					// 每一秒返回一次, 如何区分: 超时返回?  带任务返回?
					// 锁 + 双重判断.
				while (taskQue_.size() == 0 /* && isPoolRunning_  */)
				{

					// 线程池结束, 回收线程资源. 
					if (!isPoolRunning_)
					{
						threads_.erase(threadid);
						std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
						exitCond_.notify_all();
						return; // 线程函数结束,线程结束. 
					}

					if (poolMode_ == PoolMode::MODE_CACHED)
					{
						// 条件变量, 超时返回, no_timeout timeout.
						if (std::cv_status::timeout == notEmpty_.wait_for(lock, std::chrono::seconds(1)))
						{
							auto now = std::chrono::high_resolution_clock().now();
							auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);
							if (dur.count() > THREAD_MAX_IDLE_TIME &&
								curThreadSize_ > initThreadSize_)
							{
								// 开始回收当前线程.
								// 记录线程数量相关变量的值修改.
								// 把线程对象从线程列表容器中删除. 
								// threadId => thread 对象 => 删除
								threads_.erase(threadid);
								idleThreadSize_--;
								curThreadSize_--;
								std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
								return;
							}
						}
					}
					else
					{
						// 等待 notEmpty 条件.
						notEmpty_.wait(lock);
					}
				}

				idleThreadSize_--;

				// 从任务队列中取出任务
				task = taskQue_.front();
				taskQue_.pop();
				taskSize_--;
				std::cout << "tid:" << std::this_thread::get_id() << " 成功获取任务!" << std::endl;

				// 如果依然有剩余任务, 通知其他线程执行任务.
				if (taskQue_.size() > 0)
				{
					notEmpty_.notify_all();
				}

				// 取出一个任务, 进行通知, 通知可以继续提交生产任务.
				notFull_.notify_all();
			}	// 出作用域释放掉锁, 让其他线程执行任务.

			if (task != nullptr)
			{
				task(); // 执行 function<void()>.  
			}
			idleThreadSize_++;
			lastTime = std::chrono::high_resolution_clock().now(); // 更新线程执行完任务的时间.
		}


		// 如果有正在执行的任务, 任务结束后, isPoolRunning 为 false, 进不去 while 循环, 需要在循环外回收线程.
		//threads_.erase(threadid);
		//std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
		//exitCond_.notify_all();
	}

	// 检查 pool 的运行状态.
	bool checkRunningState() const
	{
		return isPoolRunning_;
	}

private:
	//std::vector<std::unique_ptr<Thread>> threads_; // 线程列表.

	std::unordered_map<int, std::unique_ptr<Thread>> threads_; // 线程列表.
	int initThreadSize_;						   // 初始的线程数量.
	int threadSizeThreshold_;					   // 线程数量上限阀值.
	std::atomic_int curThreadSize_;				   // 记录当前线程池里面线程总数量.
	std::atomic_int idleThreadSize_;			   // 空闲线程数量.

	// Task任务  =》 函数对象
	using Task = std::function<void()>;
	std::queue<Task>   taskQue_;
	//std::queue<std::shared_ptr<Task>> taskQue_; // 任务队列.
	std::atomic_int taskSize_;	   // 任务数量.
	int taskQueMaxThreshold_;	   // 任务队列数量上限阀值.

	std::mutex taskQueMtx_;		   // 保证任务队列的线程安全.
	std::condition_variable notFull_; // 表示任务队列不满.
	std::condition_variable notEmpty_;// 表示任务队列不空.
	std::condition_variable exitCond_; // 等待线程资源全部回收.

	PoolMode poolMode_;			// 工作模式.
	std::atomic_bool isPoolRunning_; // 表示当前线程的启动状态.
};


#endif