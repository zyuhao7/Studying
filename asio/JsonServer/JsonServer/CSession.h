#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <queue>
#include <mutex>
#include <memory>
#include "const.h"
using boost::asio::ip::tcp;
using namespace std;
class CServer;

class MsgNode
{
public:
	friend class CSession;
	MsgNode(const char* msg, short max_len)
		: _cur_len(0),
		_total_len(max_len + HEAD_LENGTH)
	{
		_data = new char[_total_len + 1]();
		// //×ªÎªÍøÂç×Ö½ÚÐò
		int max_len_host = boost::asio::detail::socket_ops::host_to_network_short(max_len);
		memcpy(_data, &max_len_host, HEAD_LENGTH);
		memcpy(_data + HEAD_LENGTH, msg, max_len);
		_data[_total_len] = '\0';
	}
	MsgNode(short max_len)
		:_cur_len(0),
		_total_len(max_len)
	{
		_data = new char[_total_len + 1]();
	}
	~MsgNode()
	{
		delete[] _data;
	}
	void Clear()
	{
		::memset(_data, 0, _total_len);
		_cur_len = 0;
	}

private:
	short _cur_len;
	short _total_len;
	char* _data;
};

class CSession : public enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& ioc, CServer* server);
	~CSession();
	tcp::socket& GetSocket();
	std::string& GetUuid();
	void Start();
	void Send(char* msg, short max_len);
	void Send(std::string msg);
	void Close();
	 std::shared_ptr<CSession> Shared_self();

private:
	void HandleRead(const boost::system::error_code& ec,size_t bytes_transferred, shared_ptr<CSession> self);
	void HandleWrite(const boost::system::error_code& ec, shared_ptr<CSession> self);
	tcp::socket _socket;
	std::string _uuid;
	char _data[MAX_LENGTH];
	CServer* _server;
	bool _b_close;
	std::queue<shared_ptr<MsgNode>> _send_que;
	std::mutex _send_lock;
	// body
	std::shared_ptr<MsgNode> _recv_msg_node;
	bool _b_head_parse;
	// head
	std::shared_ptr<MsgNode> _recv_head_node;
};

