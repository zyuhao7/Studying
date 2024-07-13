#include <mysql.h>
#include <string>
#include "Connection.h"	
#include "public.h"

using namespace std;

// 数据库操作类


Connection::Connection()
{
	// 初始化数据库连接资源
	_conn = mysql_init(nullptr);
}

Connection::~Connection()
{
	// 释放数据库连接资源
	if (_conn != nullptr)
		mysql_close(_conn);
}

bool Connection::connect(string ip, unsigned short port, string user, string password,
	string dbname)
{
	// 连接数据库
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(),
		password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;
}

bool Connection::update(string sql)
{
	// 更新操作 insert、delete、update
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("更新失败:" + sql);
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(string sql)
{
	// 查询操作 select
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("查询失败:" + sql);
		return nullptr;
	}
	return mysql_use_result(_conn);
}

