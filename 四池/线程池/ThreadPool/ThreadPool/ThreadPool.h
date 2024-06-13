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

//���������
class Task
{
public:
	// �û��Զ�����������,�� Task�̳�, ��д run ����, ʵ���Զ���������.	
	virtual void run() = 0;
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