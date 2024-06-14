#pragma once
#include <vector>
#include<queue>
#include<mutex>
#include<atomic>
#include <iostream>
#include<condition_variable>
#include<memory>
#include <functional>
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
		~Base() = default;
	};

	// ����������
	template<typename T>
	class Derive : public Base
	{
	public:
		Derive(T data)
			: data_(data)
		{}

	private:
		T data_;
	};

private:
	// ����һ�������ָ��.
	std::unique_ptr<Base> base_;
};


//���������
class Task
{
public:
	// �û��Զ�����������,�� Task�̳�, ��д run ����, ʵ���Զ���������.	
	virtual Any run() = 0;
};

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
	using ThreadFunc = std::function<void()>;

	Thread(ThreadFunc func);

	~Thread();

	// �����߳�.
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

	// �����̳߳صĹ���ģʽ.
	void setMode(PoolMode mode);

	// ���� task������е����߷�ֵ.
	void setTaskQueMaxThreshHold(int threshhold);

	// ���̳߳��ṩ����.
	void submitTask(std::shared_ptr<Task> sp);

	// �����̳߳�.
	void start(int initThreadNum = 4);

	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

private:
	// �����̺߳���.
	void threadFunc();

private:
	std::vector<std::unique_ptr<Thread>> threads_; // �߳��б�.
	int initThreadSize_;		   // ��ʼ���߳�����.

	std::queue<std::shared_ptr<Task>> taskQue_; // �������.
	std::atomic_int taskSize_;	   // ��������.
	int taskQueMaxThreshold_;	   // ��������������߷�ֵ.

	std::mutex taskQueMtx_;		   // ��֤������е��̰߳�ȫ.
	std::condition_variable notFull_; // ��ʾ������в���.
	std::condition_variable notEmpty_;// ��ʾ������в���.

	PoolMode poolMode_;
};

#endif