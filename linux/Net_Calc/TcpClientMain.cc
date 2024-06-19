#include "Protolcol.hpp"
#include "Socket.hpp"
#include <unistd.h>
#include <iostream>
#include <string>

// ./tcpClient serverip serverport

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage:" << argv[0] << " serverip serverport" << std::endl;
        return 0;
    }
    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    Net_work::Socket *s = new Net_work::TcpSocket();
    if (!s->BuildConnecSocketMethod(serverip, serverport))
    {
        std::cerr << "connect " << serverip << ": " << serverport << "failed! " << std::endl;
    }
    std::cout << "connect " << serverip << " : " << serverport << "success!" << std::endl;

    std::unique_ptr<Factory> factory = std::make_unique<Factory>();
    std::shared_ptr<Request> req = factory->BuildRequest(10, 20, '+');

    while (true)
    {
        req->Inc();
        send(s->GetSockFd(), &(*req), sizeof(*req), 0);
        sleep(1);
    }

    s->CloseSocket();
    return 0;
}