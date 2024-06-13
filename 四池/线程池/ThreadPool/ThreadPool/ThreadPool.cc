#include "ThreadPool.h"
#include <functional>
#include<memory>
const int TASK_MAX_THRESHHOLD = 1024;

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

	// �̵߳�ͨ�� - �ȴ���������п���.
	notFull_.wait(lock, [&]() -> bool {
		return taskQue_.size() < taskQueMaxThreshold_;
		});
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

}