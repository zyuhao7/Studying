#include "CSession.h"
#include "CServer.h"
#include "LogicSystem.h"
#include <iostream>
#include <sstream>
#include <json/reader.h>
#include <json/value.h>
#include <json/json.h>

CSession::CSession(boost::asio::io_context& ioc, CServer* server)
	:_socket(ioc),
	_server(server),
	_b_close(false),
	_b_head_parse(false)
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	_uuid = boost::uuids::to_string(a_uuid);
	_recv_head_node = make_shared<MsgNode>(HEAD_TOTAL_LEN);
}
CSession::~CSession()
{
	cout << "~CSession destruct " << endl;
}

tcp::socket& CSession::GetSocket()
{
	return _socket;
}

std::string& CSession::GetUuid()
{
	return _uuid;
}

void CSession::Start()
{
	::memset(_data, 0, MAX_LENGTH);
	_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
		std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, Shared_self()));
}

void CSession::Send(char* msg, short max_len, short msg_id)
{
	std::lock_guard<std::mutex> lock(_send_lock);
	int send_size = _send_que.size();
	if (send_size > MAX_SENDQUE)
	{
		std::cout << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE << endl;
		return;
	}
	_send_que.push(std::make_shared<SendNode>(msg, max_len, msg_id));
	// 说明当前正在发送消息.
	if (send_size > 0)
		return;
	auto& msg_node = _send_que.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msg_node->_data, msg_node->_total_len),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, Shared_self()));

}
void CSession::Send(std::string msg, short msg_id)
{
	std::lock_guard<std::mutex> lock(_send_lock);
	int send_size = _send_que.size();
	if (send_size > MAX_SENDQUE)
	{
		std::cout << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE << endl;
		return;
	}
	_send_que.push(std::make_shared<SendNode>(msg.c_str(), msg.length(), msg_id));
	// 说明当前正在发送消息.
	if (send_size > 0)
		return;

	auto& msg_node = _send_que.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msg_node->_data, msg_node->_total_len),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, Shared_self()));
}
void CSession::Close()
{
	_socket.close();
	_b_close = true;
}
std::shared_ptr<CSession> CSession::Shared_self()
{
	return shared_from_this();
}

void CSession::HandleRead(const boost::system::error_code& error, size_t bytes_transferred, shared_ptr<CSession> self)
{
	try {
		if (!error) {
			//已经移动的字符数
			int copy_len = 0;
			while (bytes_transferred > 0) {
				if (!_b_head_parse) {
					//收到的数据不足头部大小
					if (bytes_transferred + _recv_head_node->_cur_len < HEAD_TOTAL_LEN) {
						memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, bytes_transferred);
						_recv_head_node->_cur_len += bytes_transferred;

						// 继续读
						::memset(_data, 0, MAX_LENGTH);
						_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
							std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));
						return;
					}
					//收到的数据比头部多
					//头部剩余未复制的长度  处理头部完成.
					int head_remain = HEAD_TOTAL_LEN - _recv_head_node->_cur_len;
					memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, head_remain);

					//更新已处理的data长度和剩余未处理的长度
					copy_len += head_remain;
					bytes_transferred -= head_remain;

					//获取头部数据 msgid 数据
					short msg_id = 0;
					memcpy(&msg_id, _recv_head_node->_data, HEAD_ID_LEN);

					//网络字节序转化为本地字节序
					msg_id = boost::asio::detail::socket_ops::network_to_host_short(msg_id);
					std::cout << "msg_id is " << msg_id << endl;
					// id 非法
					if (msg_id > MAX_LENGTH)
					{
						std::cout << "invalid msg_id is " << msg_id << endl;
						_server->ClearSession(_uuid);
						return;
					}

					// 获取消息体长度
					short data_len = 0;
					memcpy(&data_len, _recv_head_node->_data + HEAD_ID_LEN, HEAD_DATA_LEN);
					data_len = boost::asio::detail::socket_ops::network_to_host_short(data_len);

					std::cout << "data_len is " << data_len << endl;

					//头部长度非法
					if (data_len > MAX_LENGTH) {
						std::cout << "invalid data length is " << data_len << endl;
						_server->ClearSession(_uuid);
						return;
					}

					// 构建消息体[msg_id, data_len, body]
					_recv_msg_node = make_shared<RecvNode>(data_len, msg_id);

					//消息的长度小于头部规定的长度，说明数据未收全，则先将部分消息放到接收节点里
					if (bytes_transferred < data_len) {
						memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
						_recv_msg_node->_cur_len += bytes_transferred;

						// 继续读
						::memset(_data, 0, MAX_LENGTH);
						_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
							std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));

						//头部处理完成
						_b_head_parse = true;
						return;
					}

					//消息的长度大于头部规定的长度
					memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, data_len);
					_recv_msg_node->_cur_len += data_len;
					copy_len += data_len;
					bytes_transferred -= data_len;
					_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';

					//cout << "receive data is " << _recv_msg_node->_data << endl;
					
					LogicSystem::GetInstance()->PostMsgToQue(make_shared<LogicNode>(shared_from_this(), _recv_msg_node));

					Json::Reader reader;
					Json::Value root;

					reader.parse(std::string(_recv_msg_node->_data, _recv_msg_node->_total_len), root);
				/*	std::cout << "recevie msg id  is " << root["id"].asInt() << " msg data is "
						<< root["data"].asString() << endl;*/

					root["data"] = "server has received msg, msg data is " + root["data"].asString();
					std::string return_str = root.toStyledString();
					Send(return_str, root["id"].asInt());


					//继续轮询剩余未处理数据
					_b_head_parse = false;
					_recv_head_node->Clear();
					if (bytes_transferred <= 0) {
						::memset(_data, 0, MAX_LENGTH);
						_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
							std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));
						return;
					}
					continue;
				}

				//已经处理完头部，处理上次未接受完的消息数据
				//接收的数据仍不足剩余未处理的
				int remain_msg = _recv_msg_node->_total_len - _recv_msg_node->_cur_len;
				if (bytes_transferred < remain_msg) {
					memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
					_recv_msg_node->_cur_len += bytes_transferred;
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));
					return;
				}
				// 接收的数据足够
				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
				_recv_msg_node->_cur_len += remain_msg;
				bytes_transferred -= remain_msg;
				copy_len += remain_msg;
				_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
				//cout << "receive data is " << _recv_msg_node->_data << endl;
				//此处将消息投递到逻辑队列
				LogicSystem::GetInstance()->PostMsgToQue(make_shared<LogicNode>(shared_from_this(), _recv_msg_node));
				
				Json::Reader reader;
				Json::Value root;
				reader.parse(std::string(_recv_msg_node->_data, _recv_msg_node->_total_len), root);
				//std::cout << "recevie msg id  is " << root["id"].asInt() << " msg data is "
				//	<< root["data"].asString() << endl;
				root["data"] = "server has received msg, msg data is " + root["data"].asString();
				std::string return_str = root.toStyledString();
				Send(return_str, root["id"].asInt());

				//继续轮询剩余未处理数据
				_b_head_parse = false;
				_recv_head_node->Clear();
				if (bytes_transferred <= 0) {
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));
					return;
				}
				continue;
			}
		}
		else {
			std::cout << "handle read failed, error is " << error.what() << endl;
			Close();
			_server->ClearSession(_uuid);
		}
	}
	catch (std::exception& e) {
		std::cout << "Exception code is " << e.what() << endl;
	}
	
}
void CSession::HandleWrite(const boost::system::error_code& ec, shared_ptr<CSession> self)
{
	try
	{
		if (!ec)
		{
			std::lock_guard<std::mutex> lock(_send_lock);
			_send_que.pop();
			if (!_send_que.empty())
			{
				auto& msg_node = _send_que.front();
				boost::asio::async_write(_socket, boost::asio::buffer(msg_node->_data, msg_node->_total_len),
					std::bind(&CSession::HandleWrite, this, std::placeholders::_1, self));
			}

		}
		else
		{
			std::cout << "handle write failed, error is " << ec.what() << endl;
			Close();
			_server->ClearSession(_uuid);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception code : " << e.what() << endl;
	}
}

LogicNode::LogicNode(shared_ptr<CSession> session, shared_ptr<RecvNode> recvnode)
	:_session(session),
	_recvnode(recvnode)
{

}