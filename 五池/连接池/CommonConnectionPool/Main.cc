#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "Connection.h"
#include "CommonConnectionPool.h"
using namespace std;

int main()
{

	// 单线程:1000、 5000、 10000
	//clock_t begin = clock();
	//for (int i = 0;i < 10000;++i)
	//{
	//	Connection conn;
	//	char sql[1024] = { 0 };
	//	sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//		"zhang san", 20, "male");
	//	conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//	conn.update(sql);
	//}
	//clock_t end = clock();
	//cout << (end - begin) << "ms" << endl;
	
	 //单线程连接池.
	//clock_t begin = clock();
	//ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//for (int i = 0;i < 10000;++i)
	//{
	//	shared_ptr<Connection> sp = cp->getConnection();
	//	char sql[1024] = { 0 };
	//	sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//		"zhang san", 20, "male");
	//	sp->update(sql);
	//}
	//clock_t end = clock();
	//cout << (end - begin) << "ms" << endl;


	// 四线程 无连接池.
	//Connection conn;
	//conn.connect("127.0.0.1", 3306, "root", "123456", "chat");

	//clock_t begin = clock();
	//thread t1([]() {
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		Connection conn;
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);
	//	}
	//	});
	//thread t2([]() {
	//	
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		Connection conn;
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);
	//	}
	//	});
	//thread t3([]() {
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		Connection conn;
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);
	//	}
	//	});
	//thread t4([]() {
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		Connection conn;
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);
	//	}
	//	});

	//t1.join();
	//t2.join();
	//t3.join();
	//t4.join();

	//clock_t end = clock();
	//cout << (end - begin) << "ms" << endl;


		// 四线程 有连接池. 
	//clock_t begin = clock();

	//thread t1([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//	}
	//	});

	//thread t2([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//	}
	//	});

	//thread t3([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//	}
	//	});

	//thread t4([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i)
	//	{
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//	}
	//	});
	//t1.join();
	//t2.join();
	//t3.join();
	//t4.join();

	//clock_t end = clock();
	//cout << (end - begin) << "ms" << endl;
	return 0;
}