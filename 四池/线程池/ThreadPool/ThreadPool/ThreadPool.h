#pragma once
#include <vector>
#include<queue>
#include<mutex>
#include<atomic>
#include<condition_variable>
#include<memory>
#include <functional>
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

//任务抽象类
class Task
{
public:
	// 用户自定义任务类型,从 Task继承, 重写 run 方法, 实现自定义任务处理.	
	virtual void run() = 0;
};

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
	using ThreadFunc = std::function<void()>;

	Thread(ThreadFunc func);

	~Thread();

	// 启动线程.
	void start();
private:
	ThreadFunc func_;
};


// 
class ThreadPool
{
public:
	ThreadPool();

	~ThreadPool();

	// 设置线程池的工作模式.
	void setMode(PoolMode mode);

	// 设置 task任务队列的上线阀值.
	void setTaskQueMaxThreshHold(int threshhold);

	// 给线程池提供任务.
	void submitTask(std::shared_ptr<Task> sp);

	// 开启线程池.
	void start(int initThreadNum = 4);

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// 定义线程函数.
	void threadFunc();

private:
	std::vector<std::unique_ptr<Thread>> threads_; // 线程列表.
	int initThreadSize_;		   // 初始的线程数量.

	std::queue<std::shared_ptr<Task>> taskQue_; // 任务队列.
	std::atomic_int taskSize_;	   // 任务数量.
	int taskQueMaxThreshold_;	   // 任务队列数量上线阀值.

	std::mutex taskQueMtx_;		   // 保证任务队列的线程安全.
	std::condition_variable notFull_; // 表示任务队列不满.
	std::condition_variable notEmpty_;// 表示任务队列不空.

	PoolMode poolMode_;
};

#endif