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

// any����: ���Խ����������ݵ�����.
class Any
{
public:
	// ֻ�����������������������. 
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

	// ��ȡAny����洢�� data ����.
	template<typename T>
	T cast_()
	{
		// �� base_, �ҵ���ָ���	 Derive ����, ������ȡ�� data����.
		// ���� ptr => ������ ptr  RTTI  
		Derive<T>* pd = dynamic_cast<Derive<T>* >(base_.get());
		if (pd == nullptr)
		{
			throw "type is unmatch !";
		}
		return pd->data_;
	}

private:
	// ��������.
	class Base {
	public:
		virtual ~Base() = default;
	};

	// ����������
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
	// ����һ�������ָ��.
	std::unique_ptr<Base> base_;
};

// �ź�������.
class Semaphore
{
public:	
	Semaphore(int limit = 0)
		:resLimit_(limit)
	{}

	~Semaphore() = default;

	// ��ȡһ���ź�����Դ.
	void wait()
	{
		std::unique_lock<std::mutex> lock(mtx_);
		// �ȴ��ź�������Դ, û����Դ��������...
		cond_.wait(lock, [&]() -> bool {
			return resLimit_ > 0;
			});
		resLimit_--;
	}

	// ����һ���ź�����Դ.
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
//���������
class Task
{
public:
	Task();
	~Task() = default;

	void exec();
	void setResult(Result* res);
	// �û��Զ�����������,�� Task�̳�, ��д run ����, ʵ���Զ���������.	
	virtual Any run() = 0;

private:
	Result* result_;
};

// �̳߳�֧�ֵ�ģʽ.
enum class PoolMode
{
	MODE_FIXED,  // �̶��������߳�
	MODE_CACHED, // ��̬�������߳�
};

// ʵ�ֽ����ύ���̳߳ص� task ����ִ����ɺ�ķ���ֵ���� Result.
class Result
{
public:
	Result(std::shared_ptr<Task> task, bool isValid = true);
	~Result() = default;


	// ����1:
	void setVal(Any any);

	// ����2:
	Any get();


private:
	Any any_;       // �洢����ķ���ֵ.
	Semaphore sem_; // �߳�ͨ���ź�.
	std::shared_ptr<Task> task_; // ָ���Ӧ��ȡ����ֵ���������.
	std::atomic_bool isVaild_;   // ����ֵ�Ƿ���Ч.
};


// �߳�����. 
class Thread
{
public:
	using ThreadFunc = std::function<void(int)>;

	Thread(ThreadFunc func);

	~Thread();

	// �����߳�.
	void start();

	// ��ȡ�߳� id.
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

	// �����̳߳صĹ���ģʽ.
	void setMode(PoolMode mode);

	// ���� task������е����߷�ֵ.
	void setTaskQueMaxThreshHold(int threshhold);

	// �����̳߳� cached ģʽ�� �߳���ֵ.
	void setThreadMaxSize(int threshold);

	// ���̳߳��ṩ����.
	Result submitTask(std::shared_ptr<Task> sp);

	// �����̳߳�.
	void start(int initThreadNum = 4);

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// �����̺߳���.
	void threadFunc(int threadid);

	// ��� pool ������״̬.
	bool checkRunningState() const;

private:
	//std::vector<std::unique_ptr<Thread>> threads_; // �߳��б�.

	std::unordered_map<int,std::unique_ptr<Thread>> threads_; // �߳��б�.
	int initThreadSize_;						   // ��ʼ���߳�����.
	int threadSizeThreshold_;					   // �߳��������޷�ֵ.
	std::atomic_int curThreadSize_;				   // ��¼��ǰ�̳߳������߳�������.
	std::atomic_int idleThreadSize_;			   // �����߳�����.


	std::queue<std::shared_ptr<Task>> taskQue_; // �������.
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