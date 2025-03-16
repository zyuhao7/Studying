#include "CSession.h"
#include "CServer.h"
#include <iostream>

CSession::CSession(boost::asio::io_context& ioc, CServer* server)
	: _socket(ioc),
	_server(server),
	_b_close(false),
	_b_head_parse(false)
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	_uuid = boost::uuids::to_string(a_uuid);
	_recv_head_node = std::make_shared<MsgNode>(HEAD_LENGTH);
}
CSession::~CSession()
{
	cout << " CSession destruct " << endl;
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
	::memset(_recv_msg_node->_data, 0, MAX_LENGTH);
	_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
		std::bind(&CSession::HandleRead, this, placeholders::_1, std::placeholders::_2, SharedSelf()));
}
void CSession::Send(char* msg, int max_length)
{
	bool pending = false;
	std::lock_guard<std::mutex> lock(_send_lock);
	if (_send_que.size() > 0)
		pending = true;
	_send_que.push(make_shared<MsgNode>(msg, max_length));
	if (pending) 
		return;
	auto& msgnode = _send_que.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
		std::bind(&CSession::HandleWrite, this,  std::placeholders::_1, SharedSelf()));


}
void CSession::Close()
{
	_socket.close();
	_b_close = true;
}
std::shared_ptr<CSession> CSession::SharedSelf()
{
	return shared_from_this();
}



void CSession::HandleRead(const boost::system::error_code& ec, size_t bytes_tranferred, shared_ptr<CSession> self_shared)
{
	if (!ec)
	{
		// 已经移动的字数
		int copy_len = 0;
		// 已经接收到数据
		while (bytes_tranferred > 0)
		{
			// 头部解析没完成
			if (!_b_head_parse)
			{
				// 收到的数据不足头部大小
				if (bytes_tranferred + _recv_head_node->_cur_len < HEAD_LENGTH)
				{
					memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, bytes_tranferred);
					_recv_head_node->_cur_len += bytes_tranferred;
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self_shared));
					return;
				}
				// 收到的数据比头部多
				// 头部剩余未复制的长度
				int head_remain = HEAD_LENGTH - _recv_head_node->_cur_len;
				memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, head_remain);
				// /更新已处理的data长度和剩余未处理的长度
				copy_len += head_remain;
				bytes_tranferred -= head_remain;

				// 获取头部数据
				short data_len = 0;
				memcpy(&data_len, _recv_head_node->_data, HEAD_LENGTH);
				cout << "data_len is " << data_len<<endl;

				// 头部非法长度
				if (data_len > MAX_LENGTH)
				{
					std::cout << "invalid data length is " << data_len << endl;
					_server->ClearSession(_uuid);
					return;
				}
				_recv_msg_node = make_shared<MsgNode>(data_len);

				// 消息长度小于头部规定的长度, 说明数据未收全, 则先存部分.
				if (bytes_tranferred < data_len)
				{
					memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_tranferred);
					_recv_msg_node->_cur_len += bytes_tranferred;
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self_shared));
					// 头部处理完成
					_b_head_parse = true;
					return;
				}
				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_tranferred);
				_recv_msg_node->_cur_len += bytes_tranferred;
				copy_len += data_len;
				bytes_tranferred -= data_len;
				_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
				cout << "receive data is " << _recv_msg_node->_data << endl;

				//此处可以调用Send发送测试
				Send(_recv_msg_node->_data, data_len);

				// 继续轮询剩余未处理数据
				_b_head_parse = false;
				_recv_head_node->clear();
				if (bytes_tranferred <= 0)
				{
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self_shared));
					return;
				}
				continue;
			}

			// 已经处理完头部, 处理上次未接收完全的消息数据
			// 接收的消息仍然不足剩余未处理的
			int remain_msg = _recv_msg_node->_total_len - _recv_msg_node->_cur_len;
			if (bytes_tranferred < remain_msg)
			{
				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
				_recv_msg_node->_cur_len += remain_msg;
				::memset(_data, 0, MAX_LENGTH);
				_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
					std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self_shared));
				return;
			}
			memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
			_recv_msg_node->_cur_len += remain_msg;
			bytes_tranferred -= remain_msg;
			copy_len += remain_msg;
			_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
			cout << "receive data is " << _recv_msg_node->_data << endl;

			//此处可以调用Send发送测试
			Send(_recv_msg_node->_data, _recv_msg_node->_total_len);

			//继续轮询剩余未处理数据
			_b_head_parse = false;
			_recv_head_node->clear();
			if (bytes_tranferred <= 0) {
				::memset(_data, 0, MAX_LENGTH);
				_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
					std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self_shared));
				return;
			}
			continue;
		}
	}
	else
	{
		std::cout << "handle read failed, error is " << ec.what() << endl;
		Close();
		_server->ClearSession(_uuid);
	}

}
void CSession::HandleWrite(const boost::system::error_code& ec, shared_ptr<CSession> self_shared)
{
	if (!ec)
	{
		std::lock_guard<std::mutex> lock(_send_lock);
		cout << "Send data is " << _send_que.front()->_data + HEAD_LENGTH << endl;
		_send_que.pop();
		if (!_send_que.empty())
		{
			auto& msgnode = _send_que.front(); _send_que.pop();
			boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
				std::bind(&CSession::HandleWrite, this, std::placeholders::_1, SharedSelf()));
		}
	}
	else
	{
		cout << "Handle write failed, error is " << ec.what() << endl;
		Close();
		_server->ClearSession(_uuid);
	}
}