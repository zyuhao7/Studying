#include "Protolcol.hpp"
#include "Socket.hpp"
#include "TcpServer.hpp"
#include <unistd.h>
#include <iostream>
#include <memory>
using namespace Net_work;

void HandleRequest(Socket *sockp)
{
    while (true)
    {
        struct Request req;
        recv(sockp->GetSockFd(), &req, sizeof(req), 0);
        req.Debug();
    }
}

// ./tcpServer port
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " port " << std::endl;
        return 0;
    }

    uint16_t localport = std::stoi(argv[1]);
    std::unique_ptr<TcpServer> svr(new TcpServer(localport, HandleRequest));
    svr->loop();
    return 0;
}