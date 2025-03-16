#include <cstdlib>
#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include<memory>

using  boost::asio::ip::tcp;
using namespace std;
const int max_length = 1024;
typedef std::shared_ptr<tcp::socket> socket_ptr;
std::set<std::shared_ptr<std::thread>> thread_set;

void session(socket_ptr sock)
{
	try {
		for (;;)
		{
			char data[max_length];
			memset(data, '\0', max_length);
			boost::system::error_code ec;
			size_t length = sock->read_some(boost::asio::buffer(data ,max_length), ec);
			if (ec == boost::asio::error::eof)
			{
				cout << "Connection closed by client" << endl;
				break;
			}
			else if (ec)
			{
				throw boost::system::system_error(ec);
			}
			cout << "Receive from client:" << sock->remote_endpoint().address().to_string() << endl;
			cout << "Receive msg is " << data << endl;
			//回传数据
			boost::asio::write(*sock, boost::asio::buffer(data, length));
		}
	}
	catch (std::exception& e)
	{
		cerr << "Exception in thread: " << e.what() << endl;
	}
}

void server(boost::asio::io_context& ioc, unsigned short port)
{
	tcp::acceptor a(ioc, tcp::endpoint(tcp::v4(), port));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(ioc));
		a.accept(*sock);
		auto t = std::make_shared<std::thread>(session, sock);
		thread_set.insert(t);
	}
}

int main()
{
	try {
		boost::asio::io_context ioc;
		server(ioc, 10086);
		for (auto& t : thread_set)
		{
			t->join();
		}
	}
	catch (std::exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
	}
	return 0;
}

