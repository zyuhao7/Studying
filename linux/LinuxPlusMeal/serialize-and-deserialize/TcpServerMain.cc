#include "Protocol.hpp"
#include "TcpServer.hpp"
#include "Calculate.hpp"
#include "Socket.hpp"
#include <iostream>
#include <memory>
#include <unistd.h>

using namespace Net_work;
using namespace Protocol;
using namespace CalCulateNS;

// 网络负责IO发送
// HandlerRequest字节流数据解析和调用业务处理方法的
// 处理报文的方法
std::string HandlerRequest(std::string &inbufferstream, bool *error_code)
{
    *error_code = true;
    // 0. 计算机对象
    Calculate calculte;

    // 1. 构建响应对象
    std::unique_ptr<Protocol::Factory> factory = std::make_unique<Protocol::Factory>();
    auto req = factory->BuildRequest();

    // 2. 分析字节流，看是否有一个完整的报文
    std::string total_resp_string;
    std::string message;
    while (Decode(inbufferstream, &message))
    {
        std::cout << message << "---- messge" << std::endl;

        // 3. 我一定读到了一个完整的报文，可以进行反序列化啦！
        if (!req->Deserialize(message))
        {
            std::cout << "Deserialize error" << std::endl;
            *error_code = false;
            return std::string();
        }
        std::cout << "Deserialize success" << std::endl;
        // 4. 业务处理了
        auto resp = calculte.Cal(req);
        // 5. 序列化response
        std::string send_string;
        resp->Serialize(&send_string); // "result code"
        // 6. 构建完成的字符串级别的响应报文
        send_string = Encode(send_string);
        // 7. 发送
        total_resp_string += send_string;
    }
    return total_resp_string;
}

// ./server port
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage : " << argv[0] << " port" << std::endl;
        return 0;
    }
    uint16_t localport = std::stoi(argv[1]);

    //    Daemon(false, false);
    std::unique_ptr<TcpServer> svr(new TcpServer(localport, HandlerRequest));

    svr->Loop();

    return 0;
}
