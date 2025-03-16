#pragma once
#include <boost/asio.hpp>
#include "CSession.h"
#include <memory.h>
#include <map>
using namespace std;
using boost::asio::ip::tcp;
class CServer
{
public:
	CServer(boost::asio::io_context& io_context, short port);
	void ClearSession(string uuid);

private:
	void HandleAccept(shared_ptr<CSession>, const boost::system::error_code& ec);
	void StartAccept();
	boost::asio::io_context& _ioc;
	short _port;
	tcp::acceptor _acceptor;
	std::map<string, shared_ptr<CSession>> _sessions;
};

