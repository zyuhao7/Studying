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
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

// any类型: 可以接受任意数据的类型.
class Any
{
public:
	// 只负责接受任意其他类型数据. 
	template<typename T> // T int Derive<int>
	Any(T data)
		:base_(std::make_unique<Derive<T>>(data))
	{}

	Any() = default;
	~Any() = default;
	Any(const Any&) = delete;
	Any& operator=(const Any&) = delete;
	Any(Any&&) = default;
	Any& operator=(Any&&) = default;

	// 提取Any对象存储的 data 数据.
	template<typename T>
	T cast_()
	{
		// 有 base_, 找到所指向的	 Derive 对象, 从里面取出 data数据.
		// 基类 ptr => 派生类 ptr  RTTI  
		Derive<T>* pd = dynamic_cast<Derive<T>* >(base_.get());
		if (pd == nullptr)
		{
			throw "type is unmatch !";
		}
		return pd->data_;
	}

private:
	// 基类类型.
	class Base {
	public:
		virtual ~Base() = default;
	};

	// 派生类类型
	template<typename T>
	class Derive : public Base
	{
	public:
		Derive(T data)
			: data_(data)
		{}

		T data_;
	};

private:
	// 定义一个基类的指针.
	std::unique_ptr<Base> base_;
};

// 信号量类型.
class Semaphore
{
public:	
	Semaphore(int limit = 0)
		:resLimit_(limit)
	{}

	~Semaphore() = default;

	// 获取一个信号量资源.
	void wait()
	{
		std::unique_lock<std::mutex> lock(mtx_);
		// 等待信号量有资源, 没有资源就阻塞着...
		cond_.wait(lock, [&]() -> bool {
			return resLimit_ > 0;
			});
		resLimit_--;
	}

	// 增加一个信号量资源.
	void post()
	{
		std::unique_lock<std::mutex> lock(mtx_);
		resLimit_++;
		cond_.notify_all();
	}

private:
	int resLimit_;
	std::mutex mtx_;
	std::condition_variable cond_;
};

class Result;
//任务抽象类
class Task
{
public:
	Task();
	~Task() = default;

	void exec();
	void setResult(Result* res);
	// 用户自定义任务类型,从 Task继承, 重写 run 方法, 实现自定义任务处理.	
	virtual Any run() = 0;

private:
	Result* result_;
};

// 线程池支持的模式.
enum class PoolMode
{
	MODE_FIXED,  // 固定数量的线程
	MODE_CACHED, // 动态增长的线程
};

// 实现接收提交到线程池的 task 任务执行完成后的返回值类型 Result.
class Result
{
public:
	Result(std::shared_ptr<Task> task, bool isValid = true);
	~Result() = default;


	// 问题1:
	void setVal(Any any);

	// 问题2:
	Any get();


private:
	Any any_;       // 存储任务的返回值.
	Semaphore sem_; // 线程通信信号.
	std::shared_ptr<Task> task_; // 指向对应获取返回值的任务对象.
	std::atomic_bool isVaild_;   // 返回值是否有效.
};


// 线程类型. 
class Thread
{
public:
	using ThreadFunc = std::function<void(int)>;

	Thread(ThreadFunc func);

	~Thread();

	// 启动线程.
	void start();

	// 获取线程 id.
	int getId() const;
private:
	ThreadFunc func_;
	static int generateId_;
	int threadId_;
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

	// 设置线程池 cached 模式下 线程阈值.
	void setThreadMaxSize(int threshold);

	// 给线程池提供任务.
	Result submitTask(std::shared_ptr<Task> sp);

	// 开启线程池.
	void start(int initThreadNum = 4);

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// 定义线程函数.
	void threadFunc(int threadid);

	// 检查 pool 的运行状态.
	bool checkRunningState() const;

private:
	//std::vector<std::unique_ptr<Thread>> threads_; // 线程列表.

	std::unordered_map<int,std::unique_ptr<Thread>> threads_; // 线程列表.
	int initThreadSize_;						   // 初始的线程数量.
	int threadSizeThreshold_;					   // 线程数量上限阀值.
	std::atomic_int curThreadSize_;				   // 记录当前线程池里面线程总数量.
	std::atomic_int idleThreadSize_;			   // 空闲线程数量.


	std::queue<std::shared_ptr<Task>> taskQue_; // 任务队列.
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