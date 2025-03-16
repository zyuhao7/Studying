#include <iostream>
#include <thread>
#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio::ip;

const int MAX_LENGTH = 1024 * 2;
const int HEAD_LENGTH = 2;

int main()
{
	try
	{
		// 创建对端
		boost::asio::io_context ioc;
		boost::asio::ip::tcp::endpoint ep(address::from_string("127.0.0.1"), 10086);

		// 连接
		tcp::socket sock(ioc);
		boost::system::error_code ec = boost::asio::error::host_not_found;
		sock.connect(ep, ec);
		if (ec)
		{
			cout << "connect failed, code is " << ec.value() << " error msg is " << ec.message();
			return 0;
		}

		// 发送线程
		std::thread sendthread([&sock]() {
			for (;;)
			{
				this_thread::sleep_for(std::chrono::milliseconds(2));
				const char* request = "hello world!";
				size_t request_length = strlen(request);
				char send_data[MAX_LENGTH] = { 0 };
				memcpy(send_data, &request_length, 2);
				memcpy(send_data + 2, request, request_length);
				boost::asio::write(sock, boost::asio::buffer(send_data, request_length + 2));
			}
			});

		// 接收线程
		std::thread receive ([&sock]() {
			for (;;) {
				this_thread::sleep_for(std::chrono::milliseconds(2));
				cout << "begin to receive..." << endl;
				char reply_head[HEAD_LENGTH];
				size_t reply_length = boost::asio::read(sock, boost::asio::buffer(reply_head, HEAD_LENGTH));
				short msglen = 0;
				memcpy(&msglen, reply_head, HEAD_LENGTH);
				char msg[MAX_LENGTH] = { 0 };
				size_t  msg_length = boost::asio::read(sock, boost::asio::buffer(msg, msglen));

				std::cout << "Reply is: ";
				std::cout.write(msg, msglen) << endl;
				std::cout << "Reply len is " << msglen;
				std::cout << "\n";
			}
			});
		sendthread.join();
		receive.join();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception is " << e.what() << endl;
	}

	return 0;
}
