#pragma once
#include <boost/asio.hpp>
#include <iostream>
using boost::asio::ip::tcp;
using namespace std;
class Session
{
public:
	Session(boost::asio::io_context& ioc) : _socket(ioc)
	{}
	tcp::socket& Socket()
	{
		return _socket;
	}
	void Start();
private:
	void handle_read(const boost::system::error_code& ec, size_t bytes_transfered);
	void handle_write(const boost::system::error_code& ec);
	tcp::socket _socket;
	enum { max_length = 1024 };
	char _data[max_length];
};

class Server
{
public:
	Server(boost::asio::io_context& ioc, unsigned short port);

private:
	void start_accept();
	void handle_accept(Session* new_session, const boost::system::error_code& ec);
	boost::asio::io_context& _ioc;
	tcp::acceptor _acceptor;
};
		