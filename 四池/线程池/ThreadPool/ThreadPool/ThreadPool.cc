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

// 设置线程池的工作模式.
void ThreadPool::setMode(PoolMode mode)
{
	poolMode_ = mode;
}


// 设置 task任务队列的上线阀值.
void ThreadPool::setTaskQueMaxThreshHold(int threshold)
{
	taskQueMaxThreshold_ = threshold;
}

// 给线程池提供任务. 用户生产任务.
void ThreadPool::submitTask(std::shared_ptr<Task> sp)
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
		return;
	}

	// 如果有空余, 把任务放入任务队列.
	taskQue_.emplace(sp);
	taskSize_++;

	// 因为放了任务, 任务队列肯定不为空, 在 notEmpty_ 上进行通知.
	notEmpty_.notify_all();
}

// 开启线程池.
void ThreadPool::start(int initThreadNum)
{
	// 记录初始线程个数.
	initThreadSize_ = initThreadNum;
	
	// 创建线程对象.
	for (int i = 0;i < initThreadSize_; ++i)
	{
		// 创建 thread 线程对象的时候, 把线程函数给 thread 线程对象.
		std::unique_ptr<Thread>  ptr = std::make_unique<Thread>(std::bind(&ThreadPool::threadFunc, this));
		threads_.emplace_back(std::move(ptr));
	}

	// 启动所有线程.
	for (int i = 0;i < initThreadSize_; ++i)
	{
		threads_[i]->start();
	}

}

// 定义线程函数.
void ThreadPool::threadFunc()
{
	for (;;)
	{
		std::shared_ptr<Task> task;
		// 加锁.
		{
			std::cout << "tid:" << std::this_thread::get_id() << " 尝试获取锁....!" << std::endl;
			std::unique_lock<std::mutex> lock(taskQueMtx_);
			std::cout << "tid:" << std::this_thread::get_id() << " 获取锁!" << std::endl;
			// 等待 notEmpty 条件.
			notEmpty_.wait(lock, [&]() -> bool {
				return taskQue_.size() > 0;
				});

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
			task->run();
		}
	}
}


////////////////////// 线程方法实现 ///////////////////////////////////////
Thread::Thread(ThreadFunc func)
	:func_(func)
{
}

Thread::~Thread(){}

// 启动线程.
void Thread::start()
{
	// 创建一个线程来执行一个线程函数.
	std::thread t(func_);
	t.detach();		//设置分离线程.
}