#include "connection.h"
#include <iostream>

using namespace boost;
using namespace std;

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
	catch (system::system_error& e) {
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

void use_buffer_str()
{
	asio::const_buffers_1 output_buf = asio::buffer("Hello, World!\n");
}

void use_buffer_array()
{
	const size_t BUF_SIZE_BYTES = 20;
	std::unique_ptr<char[]> buf(new char[BUF_SIZE_BYTES]);
	auto input_buf = asio::buffer((void*)buf.get(), BUF_SIZE_BYTES);
}

void use_const_buffer()
{
	std::string buf = "hello world!";
	asio::const_buffer asio_buf = asio::buffer(buf.c_str(), buf.length());
	std::vector<asio::const_buffer> buffers_sequence;
	buffers_sequence.push_back(asio_buf);
}

void use_stream_buffer()
{
	asio::streambuf buf;
	std::ostream output(&buf);

	output << "Message1\n Message2";

	std::istream input(&buf);
	std::string message1;
	std::getline(input, message1);
	cout << message1 << endl;
}

void write_to_socket(asio::ip::tcp::socket& sock)
{
	std::string buf = "hello world!";
	std::size_t total_bytes_written = 0;
	// 循环写入数据
	//write_some()函数会尽可能多地写入数据，但不保证一定会写入所有数据
	while (total_bytes_written != buf.length())
	{
		total_bytes_written += sock.write_some(asio::buffer(buf.c_str() + total_bytes_written,
			buf.length() - total_bytes_written));
	}
}

int send_data_by_write_some()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);
		write_to_socket(sock);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int send_data_by_send()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	try {

		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);
		std::string buf = "hello world!";
		int send_length = asio::send(sock, asio::buffer(buf.c_str(), buf.length());
		if (send_length <= 0)
		{
			cout << "send failed!" << endl;
			return 0;
		}
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int send_data_by_write()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	try {

		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);
		std::string buf = "hello world!";
		int send_length = asio::write(sock, asio::buffer(buf.c_str(), buf.length()));
		if (send_length <= 0)
		{
			cout << "send failed!" << endl;
			return 0;
		}
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

std::string  read_from_socket(asio::ip::tcp::socket& sock)
{
	const unsigned char MESSAGE_SIZE = 7;
	char buf[MESSAGE_SIZE];
	std::size_t total_bytes_read = 0;
	while (total_bytes_read != MESSAGE_SIZE)
	{
		total_bytes_read += sock.read_some(asio::buffer(buf + total_bytes_read,
			MESSAGE_SIZE - total_bytes_read));
	}
	return std::string(buf, total_bytes_read);
}

int read_data_by_read_some()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;

	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);
		read_from_socket(sock);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int read_data_by_receive()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;

	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);
		
		const unsigned char MESSAGE_SIZE = 7;
		char buf[MESSAGE_SIZE];
		int bytes_received = sock.receive(asio::buffer(buf), MESSAGE_SIZE);
		if (bytes_received <= 0)
		{
			cout << "receive failed!" << endl;
			return 0;
		}
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int read_data_by_receive()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;

	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);
		
		const unsigned char MESSAGE_SIZE = 7;
		char buf[MESSAGE_SIZE];
		int bytes_received = sock.receive(asio::buffer(buf), MESSAGE_SIZE);
		if (bytes_received <= 0)
		{
			cout << "receive failed!" << endl;
			return 0;
		}
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int read_data_by_read()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;

	try {
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		sock.connect(ep);

		const unsigned char MESSAGE_SIZE = 7;
		char buf[MESSAGE_SIZE];
		int bytes_received = asio::read(sock, asio::buffer(buf, MESSAGE_SIZE));
		if (bytes_received <= 0)
		{
			cout << "receive failed!" << endl;
			return 0;
		}
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

std::string read_data_by_until(asio::ip::tcp::socket& sock)
{
	asio::streambuf buf;
	asio::read_until(sock, buf, '\n');

	std::istream input(&buf);
	std::string message;
	std::getline(input, message);
	return message;
}

//int async_write_data()
//{
//	std::string raw_ip_address = "127.0.0.1";
//	unsigned short port_num = 3333;
//	try {
//		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
//		asio::io_context ioc;
//		asio::ip::tcp::socket sock(ioc, ep.protocol());
//		sock.connect(ep);
//		std::string buf = "hello world!";
//		async_write_data(sock, asio::buffer(buf.c_str(), buf.length()));
//	}
//	catch (system::system_error& e)
//	{
//		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what();
//		return e.code().value();
//	}
//	return 0;
//}