#pragma once
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <queue>
#include <mutex>
#include <memory>
using namespace std;
#define MAX_LENGTH 1024 * 2
#define HEAD_LENGTH 2
using boost::asio::ip::tcp;
class CServer;
class MsgNode
{
	friend class CSession;
public:
	MsgNode(char* msg, short max_length)
		: _cur_len(0),
		_total_len(max_length + HEAD_LENGTH)
	{
		_data = new char[_total_len + 1]();
		memcpy(_data, &max_length, HEAD_LENGTH);
		memcpy(_data + HEAD_LENGTH, msg, max_length);
		_data[_total_len] = '\0';
	}
	MsgNode(short max_length)
		:_total_len(max_length + HEAD_LENGTH)
	{
		_data = new char[_total_len + 1]();
	}
	~MsgNode()
	{
		delete[] _data;
	}
	void clear()
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
	void Send(char* msg, int max_length);
	void Close();
	std::shared_ptr<CSession> SharedSelf();

	

private:
	void HandleRead(const boost::system::error_code& ec, size_t bytes_tranferred, shared_ptr<CSession> self_shared);
	void HandleWrite(const boost::system::error_code& ec, shared_ptr<CSession> self_shared);
	tcp::socket _socket;
	std::string _uuid;
	char _data[MAX_LENGTH];
	CServer* _server;
	bool _b_close;
	std::queue<shared_ptr<MsgNode>> _send_que;
	std::mutex _send_lock;
	// 收到的消息结构
	std::shared_ptr<MsgNode> _recv_msg_node;
	bool _b_head_parse;
	// 收到的头部结构
	std::shared_ptr<MsgNode> _recv_head_node;
};

