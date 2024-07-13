#pragma once
#include <mysql.h>
#include<string>
#include<ctime>
#include<iostream>
using namespace std;
 /* ����MYSQL���ݿ�� CURD */

// ���ݿ������

class Connection
{
public:
	// ��ʼ�����ݿ�����
	Connection();

	// �ͷ����ݿ�������Դ

	~Connection();
	// �������ݿ�

	bool connect(string ip, unsigned short port, string user, string password, string dbname);

	// ���²��� insert��delete��update
	bool update(string sql);

	// ��ѯ���� select
	MYSQL_RES* query(string sql);

	// ˢ��һ��������ʼ�Ŀ���ʱ���.
	void refreshAliveTime() { alivetime_ = clock(); }

	// ���ش���ʱ��.
	clock_t getAliveTime() const { return clock() - alivetime_; }

private:
	MYSQL* _conn; // ��ʾ��MySQL Server��һ������
	clock_t alivetime_; // ��¼�������״̬�����ʵ���ʱ��.
};