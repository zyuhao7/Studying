#include "ThreadPool.h"
#include <functional>
#include <chrono>
#include <iostream>
#include<memory>
#include<errno.h>
const int TASK_MAX_THRESHHOLD = 4;

ThreadPool::ThreadPool()
	:initThreadSize_(0)
	, taskSize_(0)
	, taskQueMaxThreshold_(TASK_MAX_THRESHHOLD)
	,poolMode_(PoolMode::MODE_FIXED)
{}


ThreadPool::~ThreadPool()
{}

// �����̳߳صĹ���ģʽ.
void ThreadPool::setMode(PoolMode mode)
{
	poolMode_ = mode;
}


// ���� task������е����߷�ֵ.
void ThreadPool::setTaskQueMaxThreshHold(int threshold)
{
	taskQueMaxThreshold_ = threshold;
}

// ���̳߳��ṩ����. �û���������.
void ThreadPool::submitTask(std::shared_ptr<Task> sp)
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
		return;
	}

	// ����п���, ����������������.
	taskQue_.emplace(sp);
	taskSize_++;

	// ��Ϊ��������, ������п϶���Ϊ��, �� notEmpty_ �Ͻ���֪ͨ.
	notEmpty_.notify_all();
}

// �����̳߳�.
void ThreadPool::start(int initThreadNum)
{
	// ��¼��ʼ�̸߳���.
	initThreadSize_ = initThreadNum;
	
	// �����̶߳���.
	for (int i = 0;i < initThreadSize_; ++i)
	{
		// ���� thread �̶߳����ʱ��, ���̺߳����� thread �̶߳���.
		std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this));
		threads_.emplace_back(std::move(ptr));
	}

	// ���������߳�.
	for (int i = 0;i < initThreadSize_; ++i)
	{
		threads_[i]->start();
	}

}

// �����̺߳���.
void ThreadPool::threadFunc()
{
	for (;;)
	{
		std::shared_ptr<Task> task;
		// ����.
		{
			std::cout << "tid:" << std::this_thread::get_id() << " ���Ի�ȡ��....!" << std::endl;
			std::unique_lock<std::mutex> lock(taskQueMtx_);
			std::cout << "tid:" << std::this_thread::get_id() << " ��ȡ��!" << std::endl;
			// �ȴ� notEmpty ����.
			notEmpty_.wait(lock, [&]() -> bool {
				return taskQue_.size() > 0;
				});

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
			task->run();
		}
	}
}


////////////////////// �̷߳���ʵ�� ///////////////////////////////////////
Thread::Thread(ThreadFunc func)
	:func_(func)
{
}

Thread::~Thread(){}

// �����߳�.
void Thread::start()
{
	// ����һ���߳���ִ��һ���̺߳���.
	std::thread t(func_);
	t.detach();		//���÷����߳�.
}