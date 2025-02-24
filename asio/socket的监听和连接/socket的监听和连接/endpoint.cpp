#include "endpoint.h"
#include <iostream>
#include <boost/asio.hpp>
using namespace boost;

int client_end_point()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	boost::system::error_code ec;
	asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address, ec);
	if (ec.value() != 0)
	{
		std::cout << "Failed to parse the IP address. Error code = " << ec.value() << ". Message: " << ec.message();
		return ec.value();
	}
	asio::ip::tcp::endpoint ep(ip_address, port_num);
	return 0;
}

int server_end_point()
{
	unsigned short port_num = 3333;
	asio::ip::address ip_address = asio::ip::address_v6::any();
	asio::ip::tcp::endpoint ep(ip_address, port_num);
	return 0;
}

int create_tcp_socket()
{
	asio::io_context ioc;
	asio::ip::tcp protocal = asio::ip::tcp::v4();
	asio::ip::tcp::socket sock(ioc);
	boost::system::error_code ec;
	sock.open(protocal, ec);
	if (ec.value() != 0)
	{
		std::cout << "Failed to open the socket. Error code = " << ec.value() << ". Message: " << ec.message();
		return ec.value();
	}
	return 0;
}

int create_acceptor_socket()
{
	asio::io_context ioc;
	//asio::ip::tcp::acceptor acceptor(ioc);
	//asio::ip::tcp protocal = asio::ip::tcp::v4();
	//boost::system::error_code ec;	
	//acceptor.open(protocal, ec);
	//if (ec.value() != 0)
	//{
	//	std::cout << "Failed to open the acceptor socket. Error code = " << ec.value() << ". Message: " << ec.message();
	//	return ec.value();
	//}
	asio::ip::tcp::acceptor acceptor(ioc, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 3333));
	return 0;
}

int bind_acceptor_socket()
{
	unsigned short port_num = 3333;
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
	asio::io_context ioc;
	asio::ip::tcp::acceptor acceptor(ioc, ep.protocol());
	boost::system::error_code ec;
	acceptor.bind(ep, ec);
	if (ec.value() != 0)
	{
		std::cout << "Failed to bind the acceptor socket. Error code = " << ec.value() << ". Message: " << ec.message();
		return ec.value();
	}
	return 0;
}

int connect_to_end()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int dns_connect_to_end()
{
	std::string host = "llfc.club";
	std::string port = "3333";
	asio::io_context ioc;
	asio::ip::tcp::resolver::query query(host, port, asio::ip::tcp::resolver::query::numeric_service);
	asio::ip::tcp::resolver resolver(ioc);
	try
	{
		asio::ip::tcp::resolver::iterator it =  resolver.resolve(query);
		asio::ip::tcp::socket sock(ioc);
		asio::connect(sock, it);

	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int accept_new_connection()
{
	const int BACKLOG_SIZE = 30;
	unsigned short port_num = 3333;
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
	asio::io_context ioc;
	try {
		asio::ip::tcp::acceptor acceptor(ioc, ep.protocol());
		acceptor.bind(ep);
		acceptor.listen(BACKLOG_SIZE);
		asio::ip::tcp::socket sock(ioc);
		acceptor.accept(sock);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}