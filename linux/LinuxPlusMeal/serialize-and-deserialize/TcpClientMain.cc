#include "Protocol.hpp"
#include "Socket.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace Protocol;

// ./tcpclient serverip serverport
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage : " << argv[0] << " serverip serverport" << std::endl;
        return 0;
    }
    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    Net_work::Socket *conn = new Net_work::TcpSocket();
    if (!conn->BuildConnectSocketMethod(serverip, serverport))
    {
        std::cerr << "connect " << serverip << ":" << serverport << " failed" << std::endl;
    }
    std::cout << "connect " << serverip << ":" << serverport << " success" << std::endl;

    std::unique_ptr<Factory> factory = std::make_unique<Factory>();

    srand(time(nullptr) ^ getpid());
    const std::string opers = "+-*/%";
    while (true)
    {
        // 1. 构建一个请求，遵守协议
        int x = rand() % 100; //[0, 99]
        usleep(rand() % 7777);
        int y = rand() % 100; //[0,99]
        char oper = opers[rand() % opers.size()];
        std::shared_ptr<Request> req = factory->BuildRequest(x, y, oper);

        // 2. 对请求进行序列化
        std::string requeststr;
        req->Serialize(&requeststr); //

        std::cout << requeststr << std::endl;

        // for test
        std::string testreq = requeststr;
        testreq += " ";
        testreq += "= ";

        // 3. 添加自描述报头
        requeststr = Encode(requeststr);
        std::cout << requeststr << std::endl;

        // 4. 发送请求
        conn->Send(requeststr);
        std::string responsestr;
        while (true)
        {
            // 5. 读取响应
            if (!conn->Recv(&responsestr, 1024))
                break;
            // 6. 报文进行解析
            std::string response;
            if (!Decode(responsestr, &response))
                continue; // 我就不连续的处理了

            // 7.response "result code"
            auto resp = factory->BuildResponse();
            resp->Deserialize(response);

            // 8. 得到了计算结果，而且是一个结构化的数据
            std::cout << "结果: " << testreq << resp->GetResult() << "[" << resp->GetCode() << "]" << std::endl;
            break;
        }
        sleep(1);
    }

    conn->CloseSocket();
    return 0;
}