#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio::ip;
using namespace std;
const int MAX_LENGTH = 1024;

int main()
{
	try
	{
		// 创建上下文服务
		boost::asio::io_context ioc;
		// 构建 endpoint
		tcp::endpoint  remote_ep(address::from_string("127.0.0.1"), 10086);
		tcp::socket sock(ioc);
		boost::system::error_code ec = boost::asio::error::host_not_found;
		// 连接服务器
		sock.connect(remote_ep, ec);
		if (ec)
		{
			cout << "connect failed, code is " << ec.value() << "  error msg is " << ec.message() << endl;
			return 0;
		}
		// 发送数据
		std::cout << "Enter message: ";
		char request[MAX_LENGTH];
		std::cin.getline(request, MAX_LENGTH);
		size_t request_length = strlen(request); 
		boost::asio::write(sock, boost::asio::buffer(request, request_length));

		// 接收数据
		char reply[MAX_LENGTH];
		size_t reply_length = boost::asio::read(
			sock, boost::asio::buffer(reply, request_length));
		std::cout << "Reply is: ";
		std::cout.write(reply, reply_length);
		std::cout << "\n";
		getchar();
	}
	catch (const std::exception&e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	return 0;
}

