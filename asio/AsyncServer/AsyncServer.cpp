#include "Session.h"
#include <iostream>
#include <boost/asio.hpp>
int main()
{
	try
	{
		boost::asio::io_context ioc;
		using namespace std;
		Server s(ioc, 10086);
		ioc.run();
	}
	catch (const std::exception& e)
	{
		cerr << "Exception " << e.what() << endl;
	}
	return 0;
}
