#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <queue>
#include <mutex>
#include <memory>
#include "const.h"
#include "MsgNode.h"
using boost::asio::ip::tcp;
using namespace std;
class CServer;
class LogicSystem;


class CSession : public enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& ioc, CServer* server);
	~CSession();
	tcp::socket& GetSocket();
	std::string& GetUuid();
	void Start();
	void Send(char* msg, short max_len, short msg_id);
	void Send(std::string msg, short msg_id);
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
	std::queue<shared_ptr<SendNode>> _send_que;
	std::mutex _send_lock;
	// body
	std::shared_ptr<RecvNode> _recv_msg_node;
	bool _b_head_parse;
	// head
	std::shared_ptr<MsgNode> _recv_head_node;
};

class LogicNode {
	friend class LogicSystem;
public:
	LogicNode(shared_ptr<CSession>, shared_ptr<RecvNode>);
private:
	shared_ptr<CSession> _session;
	shared_ptr<RecvNode> _recvnode;
};