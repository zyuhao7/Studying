#include "CSession.h"
#include "CServer.h"

CSession::CSession(boost::asio::io_context& ioc, CServer* server)
	:_socket(ioc),
	_server(server)
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	_uuid = boost::uuids::to_string(a_uuid);
}

tcp::socket& CSession::GetSocket()
{
	return _socket;
}

string& CSession::GetUuid()
{
	return _uuid;
}

void CSession::Start()
{
	memset(_data, 0, MAX_LENGTH);
	_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
		std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
}

void CSession::Send(char* msg, int max_length)
{
	bool pending = false;
	std::lock_guard<std::mutex> lock(_send_lock);
	if (_send_que.size() > 0)
		pending = true;
	_send_que.push(make_shared<MsgNode>(msg, max_length));
	if (pending) return;
	boost::asio::async_write(_socket, boost::asio::buffer(msg, max_length),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_from_this()));
}

void CSession::HandleWrite(const boost::system::error_code& ec, shared_ptr<CSession> _self_shared)
{
	if (!ec)
	{
		std::lock_guard<std::mutex> lock(_send_lock);
		_send_que.pop();
		if (!_send_que.empty())
		{
			auto& msgnode = _send_que.front();
			boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_max_len),
				std::bind(&CSession::HandleWrite, this, std::placeholders::_1, _self_shared));
		}
	}
	else
	{
		cout << "Handle Write failed error is " << ec.what() << endl;
		_server->ClearSession(_uuid);
	}
}

void CSession::HandleRead(const boost::system::error_code& ec, size_t bytes_transfered, shared_ptr<CSession> _self_shared)
{
	if (!ec)
	{
		cout << "Read data is " << _data << endl;
		Send(_data, bytes_transfered);
		memset(_data, 0, MAX_LENGTH);
		_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
			std::bind(&CSession::HandleRead, this, std::placeholders::_1, std::placeholders::_2, _self_shared));
	}
	else
	{
		cout << "Handle Read Failed error is " << ec.what() << endl;
		_server->ClearSession(_uuid);
	}
}