#pragma once
#include<string>
#include<queue>
#include<mutex>
#include<functional>
#include<atomic>
#include<iostream>
#include<thread>
#include<memory>
#include<condition_variable>
using namespace std;
#include "Connection.h"

/* ���ӳع���ģ�� */

class ConnectionPool
{
public:
	// ��ȡ���ӳض���ʵ��.
	static ConnectionPool* getConnectionPool();

	// ���ⲿ�ṩ�ӿ�, �����ӳػ�ȡһ�����õĿ�������.
	shared_ptr<Connection> getConnection();

private:
	// ���� #1 ���캯��˽�л�.
	ConnectionPool();

	// �������ļ��м���������.
	bool loadConfigFile();

	//�����ڶ������߳���, ר�Ÿ�������������.
	void produceConnectionTask();

	// ɨ�賬�� maxIdleTime ʱ��Ŀ�������, ���ж��ڵ����ӻ���.
	void scannerConnectionTask();

	string ip_; // mysql �� ip ��ַ.
	unsigned short port_; // mysql �� �˿ں�:3306
	string username_; // mysql��¼�û���.
	string password_;  // mysql ��½����.
	string dbname_;   // ���ӵ����ݿ�����.
	int initSize_;	  //���ӳصĳ�ʼ��������.
	int maxSize_;	  // ���ӳص����������.
	int maxIdleTime_; // ���ӳص�������ʱ��.
	int connectionTimeOut_; // ���ӳػ�ȡ���ӵĳ�ʱʱ��.

	queue<Connection*> connQue_; // �洢mysql���ӵĶ���.
	mutex queMutex_;			 // ά�����Ӷ��е��̰߳�ȫ������.
	atomic_int connCnt_;		 // ��¼������������connction���ӵ�������.
	condition_variable cv;		 // ������������, �������������̺߳������̵߳�ͨ��.
};