#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

void Usage(const string& process)
{
  cout<<"Usage: " << process << " server_ip server_port " << endl;
}

enum class Status
{
  NEW,    // 新建状态.
  CONNECTING, // 正在连接
  CONNECTED, // 连接或者重连成功
  DISCONNECTED, // 重连失败
  CLOSED //连接失败
};

class ClientConnection
{
public:
    ClientConnection(uint16_t serverport, const std::string &serverip)
        : _sockfd(-1),
          _serverport(serverport),
          _serverip(serverip),
          _retry_interval(1), // 每次重新连接的间隔时间, 默认 1s
          _max_retries(5),
          _status(Status::NEW)
    {
    }
    void Connect()
    {
        // 1. 创建socket
        _sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (_sockfd < 0)
        {
            cerr << "socket error" << endl;
            exit(1);
        }

        // 2. 要不要bind？必须要有Ip和Port, 需要bind，但是不需要用户显示的bind，client系统随机端口
        // 发起连接的时候，client会被OS自动进行本地绑定
        // 2. connect
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(_serverport);
        // p:process(进程), n(网络) -- 不太准确，但是好记忆
        inet_pton(AF_INET, _serverip.c_str(), &server.sin_addr); // 1. 字符串 ip -> 4字节IP 2. 网络序列
        int n = connect(_sockfd, (struct sockaddr *)&server, sizeof(server)); // 自动进行bind哦！
        if (n < 0)
        {
            Disconnect();                   // 恢复_sockfd的默认值，是连接没有成功，不代表sockfd创建没有成功
            _status = Status::DISCONNECTED; // 没有连接成功
            return;
        }
        _status = Status::CONNECTED; // 连接成功
    }
    int SocketFd()
    {
        return _sockfd;
    }
    void Reconnect()
    {
        _status = Status::CONNECTING; // 正在重连
        int count = 0;
        while (count < _max_retries)
        {
            Connect(); // 重连
            if (_status == Status::CONNECTED)
            {
                return;
            }
            sleep(_retry_interval);
            count++;
            std::cout << "重连次数: " << count << ", 最大上限: " << _max_retries << std::endl;
        }
        _status = Status::CLOSED; // 重连失败，可以关闭了
    }
    void Disconnect()
    {
        if (_sockfd != -1)
        {
            close(_sockfd);
            _status = Status::CLOSED;
            _sockfd = -1;
        }
    }
    Status GetStatus()
    {
        return _status;
    }
    void Process()
    {
        // 简单的IO即可
        while (true)
        {
            string inbuffer;
            cout << "Please Enter# ";
            getline(cin, inbuffer);
            if(inbuffer.empty()) continue;
            
            ssize_t n = write(_sockfd, inbuffer.c_str(), inbuffer.size());
            if (n > 0)
            {
                char buffer[1024];
                ssize_t m = read(_sockfd, buffer, sizeof(buffer) - 1);
                if (m > 0)
                {
                    buffer[m] = 0;
                    cout << "echo messsge -> " << buffer << endl;
                }
                else if (m == 0) // 这里证明server端掉线了
                {
                    _status = Status::DISCONNECTED;
                    break;
                }
                else
                {
                    std::cout << "read m : " << m << "errno: " << errno << "errno string: " << strerror(errno) << std::endl;
                    _status = Status::CLOSED;
                    break;
                }
            }
            else
            {
                std::cout << "write n : " << n << "errno: " << errno << "errno string: " << strerror(errno) << std::endl;
                _status = Status::CLOSED;
                break;
            }
        }
    }
    ~ClientConnection()
    {
        Disconnect();
    }

private:
    int _sockfd;
    uint16_t _serverport;  // server port 端口号
    std::string _serverip; // server ip地址
    int _retry_interval;   // 重试时间间隔
    int _max_retries;      // 重试次数
    Status _status;        // 连接状态
};

class TcpClient
{
public:
    TcpClient(uint16_t serverport, const std::string &serverip) : _conn(serverport, serverip)
    {
    }
    void Execute()
    {
        while (true)
        {
            switch (_conn.GetStatus())
            {
            case Status::NEW:
                _conn.Connect();
                break;
            case Status::CONNECTED:
                std::cout << "连接成功, 开始进行通信." << std::endl;
                _conn.Process();
                break;
            case Status::DISCONNECTED:
                std::cout << "连接失败或者对方掉线，开始重连." << std::endl;
                _conn.Reconnect();
                break;
            case Status::CLOSED:
                _conn.Disconnect();
                std::cout << "重连失败, 退出." << std::endl;
                return; // 退出
            default:
                break;
            }
        }
    }
    ~TcpClient()
    {
    }

private:
    ClientConnection _conn; // 简单组合起来即可
};

//  ./tcp_client serverip serverport 

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    return 1;
  }
  string Ip = argv[1];
  uint16_t Port = stoi(argv[2]);
  TcpClient client(Port, Ip);
  client.Execute();
  return 0;
}
