#include "CServer.h"
int main()
{
	try {
		boost::asio::io_context  io_context;
		CServer s(io_context, 10086);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << endl;
	}
	boost::asio::io_context io_context;
	return 0;
}

//利用伪闭包实现连接保活
//异步处理增加了全双工的通信模式，增加了缓冲队列，可以让用户无感知的方式发送数据，不用关心底层数据下发的逻辑了。
//局限性在于未处理粘包问题，粘包问题交给下一节处理。