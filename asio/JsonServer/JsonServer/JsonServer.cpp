#include <iostream>
#include "CServer.h"
using namespace std;
int main()
{
	try {
		boost::asio::io_context  io_context;
		CServer s(io_context, 10086);
		io_context.run();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << endl;
	}
	boost::asio::io_context io_context;
}