#pragma once
#include "CSession.h"
#include <boost/asio.hpp>
#include <memory>
#include <map>
using namespace std;
using  boost::asio::ip::tcp;

class CServer
{
public:
	 CServer(boost::asio::io_context& ioc, short port);
	void ClearSession(std::string);
private:
	void HandleAccept(shared_ptr<CSession>, const boost::system::error_code& ec);
	void StartAccept();
	boost::asio::io_context& _ioc;
	short _port;
	boost::asio::ip::tcp::acceptor _acceptor;
	std::map<std::string, shared_ptr<CSession>> _sessions;
};

