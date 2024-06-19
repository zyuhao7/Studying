#include "ThreadPool.h"
#include <functional>
#include <chrono>
#include <iostream>
#include<memory>
#include<errno.h>
const int TASK_MAX_THRESHOLD = INT_MAX;
const int THREAD_MAX_THRESHOLD = 20;
const int THREAD_MAX_IDLE_TIME = 10; //单位:  s

ThreadPool::ThreadPool()
	:initThreadSize_(0)
	,threadSizeThreshold_(THREAD_MAX_THRESHOLD)
	,curThreadSize_(0)
	,idleThreadSize_(0)
	, taskSize_(0)
	, taskQueMaxThreshold_(TASK_MAX_THRESHOLD)
	,poolMode_(PoolMode::MODE_FIXED)
	,isPoolRunning_(false)
{}


ThreadPool::~ThreadPool()
{
	isPoolRunning_ = false;

	notEmpty_.notify_all();

	// 等待线程池里的所有线程返回,  两种状态: 阻塞 & 执行任务中.
	std::unique_lock<std::mutex> lock(taskQueMtx_);
	exitCond_.wait(lock, [&]() -> bool {
		return threads_.size() == 0;
		});
}

// 设置线程池的工作模式.
void ThreadPool::setMode(PoolMode mode)
{
	if (!checkRunningState())
		return;
	poolMode_ = mode;
}


// 设置 task任务队列的上线阀值.
void ThreadPool::setTaskQueMaxThreshHold(int threshold)
{
	if (checkRunningState())
		return;
	taskQueMaxThreshold_ = threshold;
}

// 设置线程池 cached 模式下 线程阈值.
void ThreadPool::setThreadMaxSize(int threshold)
{
	if (checkRunningState())
		return;
	if(poolMode_ == PoolMode::MODE_CACHED)
		threadSizeThreshold_ = threshold;
}

// 给线程池提供任务. 用户生产任务.
Result ThreadPool::submitTask(std::shared_ptr<Task> sp)
{
	// 获取锁.
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// 线程的通信 - 等待任务队列有空余. wait  wait_for  wait_until 
	if (!notFull_.wait_for(lock, std::chrono::seconds(2), [&]() -> bool {
		return taskQue_.size() < taskQueMaxThreshold_;
		}))
	{
		// 如果 notFull_ 等待两秒, 条件依然没有满足.
		std::cerr << "task queue is full, submit task fail." << std::endl;
		return Result(sp, false);
	}

	// 如果有空余, 把任务放入任务队列.
	taskQue_.emplace(sp);
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
		std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this,std::placeholders::_1));
		int threadId = ptr->getId();
		threads_.emplace(threadId, std::move(ptr));

		// 启动线程.
		threads_[threadId]->start();

		// 修改线程相关变量.
		curThreadSize_++;
		idleThreadSize_++;
	 }
		
	// 返回任务的 Result 对象.
	return Result(sp);
}

// 开启线程池.
void ThreadPool::start(int initThreadNum)
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
		std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this,std::placeholders::_1));
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

// 定义线程函数.
void ThreadPool::threadFunc(int threadid)
{
	auto lastTime = std::chrono::high_resolution_clock().now();
	while(isPoolRunning_)
	{
		std::shared_ptr<Task> task;
		// 加锁.
		{
			std::cout << "tid:" << std::this_thread::get_id() << " 尝试获取锁....!" << std::endl;
			std::unique_lock<std::mutex> lock(taskQueMtx_);
			std::cout << "tid:" << std::this_thread::get_id() << " 获取锁!" << std::endl;

			// cached 模式下, 有可能创建了很多线程，但是空闲时间超过 60s, 应该把多余的线程结束并且回收掉,
			// 超过 (initThreadSize_ 数量的线程要进行回收),
			// 当前时间 - 上一次线程执行的时间 > 60
			
				// 每一秒返回一次, 如何区分: 超时返回?  带任务返回?
			while (taskQue_.size() == 0)
			{
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

				// 线程池结束, 回收线程资源.
				if (!isPoolRunning_)
				{
					threads_.erase(threadid);
					std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
					exitCond_.notify_all();
					return;
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
			//task->run(); // 执行任务; 把任务的返回值通过 setVal 给到 Result.
			task->exec();
		}
		idleThreadSize_++;
		lastTime = std::chrono::high_resolution_clock().now(); // 更新线程执行完任务的时间.
	}


	// 如果有正在执行的任务, 任务结束后, isPoolRunning 为 false, 进不去 while 循环, 需要在循环外回收线程.
	threads_.erase(threadid);
	std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
	exitCond_.notify_all();
}

bool ThreadPool::checkRunningState() const
{
	return isPoolRunning_;
}


////////////////////// 线程方法实现 ///////////////////////////////////////
int Thread::generateId_ = 0;

Thread::Thread(ThreadFunc func)
	:func_(func)
	,threadId_(generateId_++)
{
}

Thread::~Thread(){}

// 启动线程.
void Thread::start()
{
	// 创建一个线程来执行一个线程函数.
	std::thread t(func_,threadId_);
	t.detach();		//设置分离线程.
}


// 获取线程 id.
int Thread::getId() const
{
	return threadId_;
}


////////////////////// Task 方法实现 ///////////////////////////////////////

Task::Task()
	:result_(nullptr)
{}

void Task::exec()
{
	if(result_ != nullptr)
		result_->setVal(run()); //多态调用.
}

void Task::setResult(Result* res)
{
	result_ = res;
}

////////////////////// Result方法实现 ///////////////////////////////////////

Result::Result(std::shared_ptr<Task> task, bool isValid)
	: task_(task)
	,isVaild_(isValid)
{
	task_->setResult(this);
}


void Result::setVal(Any any)
{
	//存储 task 的返回值. 
	this->any_ = std::move(any);
	sem_.post();
}


Any Result::get() // 用户调用的.
{
	if (!isVaild_)
	{
		return "";
	}
	sem_.wait(); // task 任务如果没有执行完, 这里会阻塞用户的线程.
	return std::move(any_);
}

