#include "CSession.h"
#include "CServer.h"
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
	_recv_head_node = make_shared<MsgNode>(HEAD_LENGTH);
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

void CSession::Send(char* msg, short max_len)
{
	std::lock_guard<std::mutex> lock(_send_lock);
	int send_size = _send_que.size();
	if (send_size > MAX_SENDQUE)
	{
		std::cout << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE << endl;
		return;
	}
	_send_que.push(std::make_shared<MsgNode>(msg, max_len));
	// ˵����ǰ���ڷ�����Ϣ.
	if (send_size > 0)
		return;
	auto& msg_node = _send_que.front();
	boost::asio::async_write(_socket, boost::asio::buffer(msg_node->_data, msg_node->_total_len),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, Shared_self()));

}
void CSession::Send(std::string msg)
{
	std::lock_guard<std::mutex> lock(_send_lock);
	int send_size = _send_que.size();
	if (send_size > MAX_SENDQUE)
	{
		std::cout << "session: " << _uuid << " send que fulled, size is " << MAX_SENDQUE << endl;
		return;
	}
	_send_que.push(std::make_shared<MsgNode>(msg.c_str(), msg.length()));
	// ˵����ǰ���ڷ�����Ϣ.
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
			//�Ѿ��ƶ����ַ���
			int copy_len = 0;
			while (bytes_transferred > 0) {
				if (!_b_head_parse) {
					//�յ������ݲ���ͷ����С
					if (bytes_transferred + _recv_head_node->_cur_len < HEAD_LENGTH) {
						memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, bytes_transferred);
						_recv_head_node->_cur_len += bytes_transferred;

						// ������
						::memset(_data, 0, MAX_LENGTH);
						_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
							std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));
						return;
					}
					//�յ������ݱ�ͷ����
					//ͷ��ʣ��δ���Ƶĳ���  ����ͷ�����.
					int head_remain = HEAD_LENGTH - _recv_head_node->_cur_len;
					memcpy(_recv_head_node->_data + _recv_head_node->_cur_len, _data + copy_len, head_remain);

					//�����Ѵ����data���Ⱥ�ʣ��δ����ĳ���
					copy_len += head_remain;
					bytes_transferred -= head_remain;

					//��ȡͷ������
					short data_len = 0;
					memcpy(&data_len, _recv_head_node->_data, HEAD_LENGTH);

					//�����ֽ���ת��Ϊ�����ֽ���
					data_len = boost::asio::detail::socket_ops::network_to_host_short(data_len);
					std::cout << "data_len is " << data_len << endl;

					//ͷ�����ȷǷ�
					if (data_len > MAX_LENGTH) {
						std::cout << "invalid data length is " << data_len << endl;
						_server->ClearSession(_uuid);
						return;
					}

					// ������Ϣ��[data_len, body]
					_recv_msg_node = make_shared<MsgNode>(data_len);

					//��Ϣ�ĳ���С��ͷ���涨�ĳ��ȣ�˵������δ��ȫ�����Ƚ�������Ϣ�ŵ����սڵ���
					if (bytes_transferred < data_len) {
						memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
						_recv_msg_node->_cur_len += bytes_transferred;

						// ������
						::memset(_data, 0, MAX_LENGTH);
						_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
							std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));

						//ͷ���������
						_b_head_parse = true;
						return;
					}

					//��Ϣ�ĳ��ȴ���ͷ���涨�ĳ���
					memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, data_len);
					_recv_msg_node->_cur_len += data_len;
					copy_len += data_len;
					bytes_transferred -= data_len;
					_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';

					cout << "receive data is " << _recv_msg_node->_data << endl;
					//�˴����Ե���Send���Ͳ���
					
					Json::Reader reader;
					Json::Value root;

					reader.parse(std::string(_recv_msg_node->_data, _recv_msg_node->_total_len), root);
					std::cout << "recevie msg id  is " << root["id"].asInt() << " msg data is "
						<< root["data"].asString() << endl;

					root["data"] = "server has received msg, msg data is " + root["data"].asString();
					std::string return_str = root.toStyledString();
					Send(return_str);


					//������ѯʣ��δ��������
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

				//�Ѿ�������ͷ���������ϴ�δ���������Ϣ����
				//���յ������Բ���ʣ��δ�����
				int remain_msg = _recv_msg_node->_total_len - _recv_msg_node->_cur_len;
				if (bytes_transferred < remain_msg) {
					memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
					_recv_msg_node->_cur_len += bytes_transferred;
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, self));
					return;
				}
				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, remain_msg);
				_recv_msg_node->_cur_len += remain_msg;
				bytes_transferred -= remain_msg;
				copy_len += remain_msg;
				_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
				cout << "receive data is " << _recv_msg_node->_data << endl;

					//�˴����Ե���Send���Ͳ���
				Json::Reader reader;
				Json::Value root;
				reader.parse(std::string(_recv_msg_node->_data, _recv_msg_node->_total_len), root);
				std::cout << "recevie msg id  is " << root["id"].asInt() << " msg data is "
					<< root["data"].asString() << endl;
				root["data"] = "server has received msg, msg data is " + root["data"].asString();
				std::string return_str = root.toStyledString();
				Send(return_str);

				//������ѯʣ��δ��������
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
