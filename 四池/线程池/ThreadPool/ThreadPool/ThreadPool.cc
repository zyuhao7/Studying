#include "ThreadPool.h"
#include <functional>
#include <chrono>
#include <iostream>
#include<memory>
#include<errno.h>
const int TASK_MAX_THRESHOLD = INT_MAX;
const int THREAD_MAX_THRESHOLD = 20;
const int THREAD_MAX_IDLE_TIME = 10; //��λ:  s

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

	// �ȴ��̳߳���������̷߳���,  ����״̬: ���� & ִ��������.
	std::unique_lock<std::mutex> lock(taskQueMtx_);
	exitCond_.wait(lock, [&]() -> bool {
		return threads_.size() == 0;
		});
}

// �����̳߳صĹ���ģʽ.
void ThreadPool::setMode(PoolMode mode)
{
	if (checkRunningState())
		return;
	poolMode_ = mode;
}


// ���� task������е����߷�ֵ.
void ThreadPool::setTaskQueMaxThreshHold(int threshold)
{
	if (checkRunningState())
		return;
	taskQueMaxThreshold_ = threshold;
}

// �����̳߳� cached ģʽ�� �߳���ֵ.
void ThreadPool::setThreadMaxSize(int threshold)
{
	if (checkRunningState())
		return;
	if(poolMode_ == PoolMode::MODE_CACHED)
		threadSizeThreshold_ = threshold;
}

// ���̳߳��ṩ����. �û���������.
Result ThreadPool::submitTask(std::shared_ptr<Task> sp)
{
	// ��ȡ��.
	std::unique_lock<std::mutex> lock(taskQueMtx_);

	// �̵߳�ͨ�� - �ȴ���������п���. wait  wait_for  wait_until 
	if (!notFull_.wait_for(lock, std::chrono::seconds(2), [&]() -> bool {
		return taskQue_.size() < taskQueMaxThreshold_;
		}))
	{
		// ��� notFull_ �ȴ�����, ������Ȼû������.
		std::cerr << "task queue is full, submit task fail." << std::endl;
		return Result(sp, false);
	}

	// ����п���, ����������������.
	taskQue_.emplace(sp);
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
		std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this,std::placeholders::_1));
		int threadId = ptr->getId();
		threads_.emplace(threadId, std::move(ptr));

		// �����߳�.
		threads_[threadId]->start();

		// �޸��߳���ر���.
		curThreadSize_++;
		idleThreadSize_++;
	 }
		
	// ��������� Result ����.
	return Result(sp);
}

// �����̳߳�.
void ThreadPool::start(int initThreadNum)
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
		std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this,std::placeholders::_1));
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

// �����̺߳���.
void ThreadPool::threadFunc(int threadid)
{
	auto lastTime = std::chrono::high_resolution_clock().now();
	while(isPoolRunning_)
	{
		std::shared_ptr<Task> task;
		// ����.
		{
			std::cout << "tid:" << std::this_thread::get_id() << " ���Ի�ȡ��....!" << std::endl;
			std::unique_lock<std::mutex> lock(taskQueMtx_);
			std::cout << "tid:" << std::this_thread::get_id() << " ��ȡ��!" << std::endl;

			// cached ģʽ��, �п��ܴ����˺ܶ��̣߳����ǿ���ʱ�䳬�� 60s, Ӧ�ðѶ�����߳̽������һ��յ�,
			// ���� (initThreadSize_ �������߳�Ҫ���л���),
			// ��ǰʱ�� - ��һ���߳�ִ�е�ʱ�� > 60
			
				// ÿһ�뷵��һ��, �������: ��ʱ����?  �����񷵻�?
			while (taskQue_.size() == 0)
			{
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

				// �̳߳ؽ���, �����߳���Դ.
				if (!isPoolRunning_)
				{
					threads_.erase(threadid);
					std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
					exitCond_.notify_all();
					return;
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
			//task->run(); // ִ������; ������ķ���ֵͨ�� setVal ���� Result.
			task->exec();
		}
		idleThreadSize_++;
		lastTime = std::chrono::high_resolution_clock().now(); // �����߳�ִ���������ʱ��.
	}


	// ���������ִ�е�����, ���������, isPoolRunning Ϊ false, ����ȥ while ѭ��, ��Ҫ��ѭ��������߳�.
	threads_.erase(threadid);
	std::cout << "threadId " << std::this_thread::get_id() << " exit! " << std::endl;
	exitCond_.notify_all();
}

bool ThreadPool::checkRunningState() const
{
	return isPoolRunning_;
}


////////////////////// �̷߳���ʵ�� ///////////////////////////////////////
int Thread::generateId_ = 0;

Thread::Thread(ThreadFunc func)
	:func_(func)
	,threadId_(generateId_++)
{
}

Thread::~Thread(){}

// �����߳�.
void Thread::start()
{
	// ����һ���߳���ִ��һ���̺߳���.
	std::thread t(func_,threadId_);
	t.detach();		//���÷����߳�.
}


// ��ȡ�߳� id.
int Thread::getId() const
{
	return threadId_;
}


////////////////////// Task ����ʵ�� ///////////////////////////////////////

Task::Task()
	:result_(nullptr)
{}

void Task::exec()
{
	if(result_ != nullptr)
		result_->setVal(run()); //��̬����.
}

void Task::setResult(Result* res)
{
	result_ = res;
}

////////////////////// Result����ʵ�� ///////////////////////////////////////

Result::Result(std::shared_ptr<Task> task, bool isValid)
	: task_(task)
	,isVaild_(isValid)
{
	task_->setResult(this);
}


void Result::setVal(Any any)
{
	//�洢 task �ķ���ֵ. 
	this->any_ = std::move(any);
	sem_.post();
}


Any Result::get() // �û����õ�.
{
	if (!isVaild_)
	{
		return "";
	}
	sem_.wait(); // task �������û��ִ����, ����������û����߳�.
	return std::move(any_);
}

