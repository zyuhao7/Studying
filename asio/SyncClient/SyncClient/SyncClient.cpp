#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio::ip;
using namespace std;
const int MAX_LENGTH = 1024 * 2;
const int HEAD_LENGTH = 2;

int main()
{
	try
	{
		boost::asio::io_context ioc;
		// 先创建对端
		tcp::endpoint ep(address::from_string("127.0.0.1"), 10086);
		// 连接.
		tcp::socket sock(ioc);
		boost::system::error_code ec = boost::asio::error::host_not_found;
		sock.connect(ep, ec);
		if (ec) {
			cout << "connect failed, code is " << ec.value() << " error msg is " << ec.message();
			return 0;
		}

		// 输入输入数据
		cout << "Enter message:";
		char request[MAX_LENGTH];
		cin.getline(request, MAX_LENGTH);
		size_t request_len = strlen(request);

		// 消息发回
		char send_data[MAX_LENGTH] = { 0 };
		memcpy(send_data, &request_len, HEAD_LENGTH);
		memcpy(send_data + HEAD_LENGTH, request, request_len);
		boost::asio::write(sock, boost::asio::buffer(send_data, request_len + 2));

		// 处理服务器返回的消息
		// 处理头
		char reply_head[MAX_LENGTH];
		size_t reply_len = boost::asio::read(sock, boost::asio::buffer(reply_head, HEAD_LENGTH));

		// 处理消息体
		short msglen = 0;
		memcpy(&msglen, reply_head, HEAD_LENGTH);
		char msg[MAX_LENGTH] = { 0 };
		size_t msg_length = boost::asio::read(sock, boost::asio::buffer(msg, msglen));

		// 打印到控制台
		std::cout << "Reply is: ";
		std::cout.write(msg, msglen) << endl;
		std::cout << "Reply len is " << msglen;
		std::cout << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << endl;
	}

	return 0;
}

