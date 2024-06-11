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

/* 连接池功能模块 */

class ConnectionPool
{
public:
	// 获取连接池对象实例.
	static ConnectionPool* getConnectionPool();

	// 给外部提供接口, 从连接池获取一个可用的空闲连接.
	shared_ptr<Connection> getConnection();

private:
	// 单例 #1 构造函数私有化.
	ConnectionPool();

	// 从配置文件中加载配置项.
	bool loadConfigFile();

	//运行在独立的线程中, 专门负责生产新连接.
	void produceConnectionTask();

	// 扫描超过 maxIdleTime 时间的空闲连接, 进行多于的连接回收.
	void scannerConnectionTask();

	string ip_; // mysql 的 ip 地址.
	unsigned short port_; // mysql 的 端口号:3306
	string username_; // mysql登录用户名.
	string password_;  // mysql 登陆密码.
	string dbname_;   // 连接的数据库名字.
	int initSize_;	  //连接池的初始化连接量.
	int maxSize_;	  // 连接池的最大连接量.
	int maxIdleTime_; // 连接池的最大空闲时间.
	int connectionTimeOut_; // 连接池获取连接的超时时间.

	queue<Connection*> connQue_; // 存储mysql连接的队列.
	mutex queMutex_;			 // 维护连接队列的线程安全互斥锁.
	atomic_int connCnt_;		 // 记录连接所建立的connction连接的总数量.
	condition_variable cv;		 // 设置条件变量, 用于连接生产线程和消费线程的通信.
};