#include <arpa/inet.h>
#include <iostream>

int main()
{
    struct sockaddr_in addrin;
    
    struct in_addr addr;
    inet_pton(AF_INET, "192.168.1.100", &addr); // 字符串 → 网络地址

    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr, ip_str, INET_ADDRSTRLEN); // 网络地址 → 字符串

    // IPv6 示例
    struct in6_addr ipv6addr;
    inet_pton(AF_INET6, "::1", &ipv6addr);

    char str[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &ipv6addr, str, sizeof(str));

    std::cout << "ipv6: " << str << std::endl;
    std::cout << "ip: " << ip_str << std::endl;
    return 0;
}
