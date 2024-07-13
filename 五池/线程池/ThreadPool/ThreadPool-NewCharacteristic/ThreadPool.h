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
const int THREAD_MAX_IDLE_TIME = 10; //��λ:  s

// �̳߳�֧�ֵ�ģʽ.
enum class PoolMode
{
	MODE_FIXED,  // �̶��������߳�
	MODE_CACHED, // ��̬�������߳�
};

// �߳�����. 
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

	// �����߳�.
	void start()
	{
		// ����һ���߳���ִ��һ���̺߳���.
		std::thread t(func_, threadId_);
		t.detach();		//���÷����߳�.
	}

	// ��ȡ�߳� id.
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

		// �ȴ��̳߳���������̷߳���,  ����״̬: ���� & ִ��������. �����������. 
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		notEmpty_.notify_all();

		exitCond_.wait(lock, [&]() -> bool {
			return threads_.size() == 0;
			});
	}


	// �����̳߳صĹ���ģʽ.
	void setMode(PoolMode mode)
	{
		if (checkRunningState())
			return;
		poolMode_ = mode;
	}


	// ���� task������е����߷�ֵ.
	void setTaskQueMaxThreshHold(int threshold)
	{
		if (checkRunningState())
			return;
		taskQueMaxThreshold_ = threshold;
	}

	// �����̳߳� cached ģʽ�� �߳���ֵ.
	void setThreadMaxSize(int threshold)
	{
		if (checkRunningState())
			return;
		if (poolMode_ == PoolMode::MODE_CACHED)
			threadSizeThreshold_ = threshold;
	}

	// ���̳߳��ṩ����.
	// ʹ�ÿɱ��ģ����, �ø� submitTask���Խ�����������
	//�����������Ĳ���.
	// pool.submitTask(sum1,10,20);
	// ����ֵ future<> 
	template<typename Func, typename... Args> // // �����۵�. decltype.
	auto submitTask(Func&& func, Args&&... args) -> std::future<decltype(func(args...))>
	{
		// ������� �����������.
		using RType = decltype(func(args...));
		auto task = std::make_shared<std::packaged_task<RType()>>(
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
		);
		std::future<RType> result = task->get_future();

		// ��ȡ��.
		std::unique_lock<std::mutex> lock(taskQueMtx_);

		// �̵߳�ͨ�� - �ȴ���������п���. wait  wait_for  wait_until 
		if (!notFull_.wait_for(lock, std::chrono::seconds(2), [&]() -> bool {
			return taskQue_.size() < taskQueMaxThreshold_;
			}))
		{
			// ��� notFull_ �ȴ�����, ������Ȼû������. 
			std::cerr << "task queue is full, submit task fail." << std::endl;
			auto task = std::make_shared<std::packaged_task<RType()>>(
				[]() -> RType {return RType();});
			(*task)();
			return task->get_future();
		}

		// ����п���, ����������������.
		// using Task = std::function<void()>;
		taskQue_.emplace([task]() {
			// ִ����������.
			(*task)();
			});
		taskSize_++;

		// ��Ϊ��������, ������п϶���Ϊ��, �� notEmpty_ �Ͻ���֪ͨ.
		notEmpty_.notify_all();

		// cached ģʽ�� ���������, ����: С���������,��Ҫ�������������Ϳ����߳�����,�ж��Ƿ���Ҫ�����߳�.
		if (poolMode_ == PoolMode::MODE_CACHED &&
			curThreadSize_ < threadSizeThreshold_ &&
			taskSize_ > idleThreadSize_)
		{
			std::cout << "create new Thread.. " << std::endl;
			// �����µ��̶߳���.
			std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));

			// �����߳�.
			threads_[threadId]->start();

			// �޸��߳���ر���.
			curThreadSize_++;
			idleThreadSize_++;
		}

		// ��������� Result ����.
		return result;
	}


	// �����̳߳�.
	void start(int initThreadNum)
	{
		// �����̳߳ص�����״̬.
		isPoolRunning_ = true;

		// ��¼��ʼ�̸߳���.
		initThreadSize_ = initThreadNum;
		curThreadSize_ = initThreadNum;

		// �����̶߳���.
		for (int i = 0;i < initThreadSize_; ++i)
		{
			// ���� thread �̶߳����ʱ��, ���̺߳����� thread �̶߳���.
			std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
			int threadId = ptr->getId();
			threads_.emplace(threadId, std::move(ptr));
			//threads_.emplace_back(std::move(ptr));
		}

		// ���������߳�.
		for (int i = 0;i < initThreadSize_; ++i)
		{
			threads_[i]->start();
			idleThreadSize_++;
		}

	}

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// �����̺߳���.
	void threadFunc(int threadid)
	{
		auto lastTime = std::chrono::high_resolution_clock().now();
		for (;;)
		{
			Task task;
			// ����.
			{
				std::cout << "tid:" << std::this_thread::get_id() << " ���Ի�ȡ��....!" << std::endl;
				std::unique_lock<std::mutex> lock(taskQueMtx_);
				std::cout << "tid:" << std::this_thread::get_id() << " ��ȡ��!" << std::endl;

				// cached ģʽ��, �п��ܴ����˺ܶ��̣߳����ǿ���ʱ�䳬�� 60s, Ӧ�ðѶ�����߳̽������һ��յ�,
				// ���� (initThreadSize_ �������߳�Ҫ���л���),
				// ��ǰʱ�� - ��һ���߳�ִ�е�ʱ�� > 60

					// ÿһ�뷵��һ��, �������: ��ʱ����?  �����񷵻�?
					// �� + ˫���ж�.
				while (taskQue_.size() == 0 /* && isPoolRunning_  */)
				{

					// �̳߳ؽ���, �����߳���Դ. 
					if (!isPoolRunning_)
					{
						threads_.erase(threadid);
						std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
						exitCond_.notify_all();
						return; // �̺߳�������,�߳̽���. 
					}

					if (poolMode_ == PoolMode::MODE_CACHED)
					{
						// ��������, ��ʱ����, no_timeout timeout.
						if (std::cv_status::timeout == notEmpty_.wait_for(lock, std::chrono::seconds(1)))
						{
							auto now = std::chrono::high_resolution_clock().now();
							auto dur = std::chrono::duration_cast<std::chrono::seconds>(now - lastTime);
							if (dur.count() > THREAD_MAX_IDLE_TIME &&
								curThreadSize_ > initThreadSize_)
							{
								// ��ʼ���յ�ǰ�߳�.
								// ��¼�߳�������ر�����ֵ�޸�.
								// ���̶߳�����߳��б�������ɾ��. 
								// threadId => thread ���� => ɾ��
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
						// �ȴ� notEmpty ����.
						notEmpty_.wait(lock);
					}
				}

				idleThreadSize_--;

				// �����������ȡ������
				task = taskQue_.front();
				taskQue_.pop();
				taskSize_--;
				std::cout << "tid:" << std::this_thread::get_id() << " �ɹ���ȡ����!" << std::endl;

				// �����Ȼ��ʣ������, ֪ͨ�����߳�ִ������.
				if (taskQue_.size() > 0)
				{
					notEmpty_.notify_all();
				}

				// ȡ��һ������, ����֪ͨ, ֪ͨ���Լ����ύ��������.
				notFull_.notify_all();
			}	// ���������ͷŵ���, �������߳�ִ������.

			if (task != nullptr)
			{
				task(); // ִ�� function<void()>.  
			}
			idleThreadSize_++;
			lastTime = std::chrono::high_resolution_clock().now(); // �����߳�ִ���������ʱ��.
		}


		// ���������ִ�е�����, ���������, isPoolRunning Ϊ false, ����ȥ while ѭ��, ��Ҫ��ѭ��������߳�.
		//threads_.erase(threadid);
		//std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
		//exitCond_.notify_all();
	}

	// ��� pool ������״̬.
	bool checkRunningState() const
	{
		return isPoolRunning_;
	}

private:
	//std::vector<std::unique_ptr<Thread>> threads_; // �߳��б�.

	std::unordered_map<int, std::unique_ptr<Thread>> threads_; // �߳��б�.
	int initThreadSize_;						   // ��ʼ���߳�����.
	int threadSizeThreshold_;					   // �߳��������޷�ֵ.
	std::atomic_int curThreadSize_;				   // ��¼��ǰ�̳߳������߳�������.
	std::atomic_int idleThreadSize_;			   // �����߳�����.

	// Task����  =�� ��������
	using Task = std::function<void()>;
	std::queue<Task>   taskQue_;
	//std::queue<std::shared_ptr<Task>> taskQue_; // �������.
	std::atomic_int taskSize_;	   // ��������.
	int taskQueMaxThreshold_;	   // ��������������޷�ֵ.

	std::mutex taskQueMtx_;		   // ��֤������е��̰߳�ȫ.
	std::condition_variable notFull_; // ��ʾ������в���.
	std::condition_variable notEmpty_;// ��ʾ������в���.
	std::condition_variable exitCond_; // �ȴ��߳���Դȫ������.

	PoolMode poolMode_;			// ����ģʽ.
	std::atomic_bool isPoolRunning_; // ��ʾ��ǰ�̵߳�����״̬.
};


#endif