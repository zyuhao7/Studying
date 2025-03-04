#include "CServer.h"
#include <iostream>

CServer::CServer(boost::asio::io_context& ioc, short port)
	:_ioc(ioc),
	_port(port),
	_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
	cout << "Server start success, Listen on port : " << _port << endl;
	StartAccept();
}

void CServer::HandleAccept(shared_ptr<CSession> new_session, const boost::system::error_code& ec)
{
	if (!ec)
	{
		new_session->Start();
		_sessions.insert(make_pair(new_session->GetUuid(), new_session));
	}
	else
	{
		cout << "session accept failed, er is " << ec.what() << endl;
	}
	StartAccept();
}

void CServer::StartAccept()
{
	shared_ptr<CSession> new_session = make_shared<CSession>(_ioc, this);
	_acceptor.async_accept(new_session->GetSocket(), std::bind(&CServer::HandleAccept,
		this, new_session, placeholders::_1));
}

void CServer::ClearSession(string uuid)
{
	_sessions.erase(uuid);
}