#pragma once
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class InetAddr
{
public:
    InetAddr(struct sockaddr_in &addr) : _addr(addr)
    {
        _port = ntohs(_addr.sin_port);
        _ip = inet_ntoa(_addr.sin_addr);
    }
    InetAddr(const std::string &ip, uint16_t port)
    {
        _ip = ip;
        _port = port;
    }
    std::string Ip() { return _ip; }
    uint16_t Port() { return _port; };
    std::string PrintDebug()
    {
        std::string info = _ip;
        info += ":";
        info += std::to_string(_port); // "127.0.0.1:4444"
        return info;
    }
    const struct sockaddr_in &GetAddr()
    {
        return _addr;
    }
    bool operator==(const InetAddr &addr)
    {
        // other code
        return this->_ip == addr._ip && this->_port == addr._port;
    }
    ~InetAddr() {}

private:
    std::string _ip;
    uint16_t _port;
    struct sockaddr_in _addr;
};