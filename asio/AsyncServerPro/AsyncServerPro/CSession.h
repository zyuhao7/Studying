#pragma once
#include "CSession.h"
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <queue>
#include <mutex>
#include <iostream>
#include <memory>

using namespace std;
#define MAX_LENGTH 1024
using boost::asio::ip::tcp;
class CServer;

class MsgNode
{
	friend class CSession;
public:
	MsgNode(char* msg, int max_len)
	{
		_data = new char[max_len];
		memcpy(_data, msg, max_len);
		_cur_len = 0;
		_max_len = max_len;
	}
	~MsgNode()
	{
		delete[] _data;
	}

private:
	int _cur_len;
	int _max_len;
	char* _data;
};

class CSession : public std::enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& ioc, CServer* server);
	~CSession()
	{
		cout << "Session destruct" << endl;
	}
	tcp::socket& GetSocket();
	string& GetUuid();
	void Start();
	void Send(char* msg, int max_length);

private:
	void HandleRead(const boost::system::error_code& ec, size_t bytes_transfered, shared_ptr<CSession> _self_shared);
	void HandleWrite(const boost::system::error_code& ec, shared_ptr<CSession> _self_shared);
	tcp::socket _socket;
	string _uuid;
	char _data[MAX_LENGTH];
	CServer* _server;
	std::queue<shared_ptr<MsgNode>> _send_que;
	std::mutex _send_lock;
};