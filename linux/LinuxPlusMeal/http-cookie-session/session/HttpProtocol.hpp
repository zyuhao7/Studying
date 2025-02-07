#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <ctime>
#include <functional>
#include "TcpServer.hpp"
#include "Session.hpp" // 引入session

const std::string HttpSep = "\r\n";
// 可以配置的
const std::string homepage = "index.html";
const std::string wwwroot = "./wwwroot";

class HttpRequest
{
public:
    HttpRequest() : _req_blank(HttpSep), _path(wwwroot)
    {
    }
    bool GetLine(std::string &str, std::string *line)
    {
        auto pos = str.find(HttpSep);
        if (pos == std::string::npos)
            return false;
        *line = str.substr(0, pos); // \r\n
        str.erase(0, pos + HttpSep.size());
        return true;
    }
    void Parse()
    {
        // 解析出来url
        std::stringstream ss(_req_line);
        ss >> _method >> _url >> _http_version;

        // 查找cookie
        std::string prefix = "Cookie: "; // 写入： Set-Cookie: sessionid=1234 提交: Cookie: sessionid=1234
        for (auto &line : _req_header)
        {
            std::string cookie;
            if (strncmp(line.c_str(), prefix.c_str(), prefix.size()) == 0) // 找到了
            {
                cookie = line.substr(prefix.size()); // 截取"Cookie: "之后的就行了
                _cookies.emplace_back(cookie);
                break;
            }
        }

        // 查找sessionid
        // sessionid=1234
        prefix = "sessionid=";
        for (const auto &cookie : _cookies)
        {
            if (strncmp(cookie.c_str(), prefix.c_str(), prefix.size()) == 0)
            {
                _sessionid = cookie.substr(prefix.size()); // 截取"sessionid="之后的就行了
                // std::cout << "_sessionid: " << _sessionid << std::endl;
            }
        }
    }
    std::string Url()
    {
        return _url;
    }
    std::string SessionId()
    {
        return _sessionid;
    }
    bool Deserialize(std::string &request)
    {
        std::string line;
        bool ok = GetLine(request, &line);
        if (!ok)
            return false;
        _req_line = line;

        while (true)
        {
            bool ok = GetLine(request, &line);
            if (ok && line.empty())
            {
                _req_content = request;
                break;
            }
            else if (ok && !line.empty())
            {
                _req_header.push_back(line);
            }
            else
            {
                break;
            }
        }

        return true;
    }
    void DebugHttp()
    {
        std::cout << "_req_line: " << _req_line << std::endl;
        for (auto &line : _req_header)
        {
            std::cout << "---> " << line << std::endl;
        }
    }
    ~HttpRequest()
    {
    }

private:
    // http报文自动
    std::string _req_line; // method url http_version
    std::vector<std::string> _req_header;
    std::string _req_blank;
    std::string _req_content;

    // 解析之后的内容
    std::string _method;
    std::string _url; // /   /dira/dirb/x.html     /dira/dirb/XX?usrname=100&&password=1234 /dira/dirb
    std::string _http_version;
    std::string _path;                 // "./wwwroot"
    std::string _suffix;               // 请求资源的后缀
    std::vector<std::string> _cookies; // 其实cookie可以有多个，因为Set-Cookie可以被写多条，测试，一条够了。
    std::string _sessionid;            // 请求携带的sessionid，仅仅用来测试
};

const std::string BlankSep = " ";
const std::string LineSep = "\r\n";

class HttpResponse
{
public:
    HttpResponse() : _http_version("HTTP/1.0"), _status_code(200), _status_code_desc("OK"), _resp_blank(LineSep)
    {
    }
    void SetCode(int code)
    {
        _status_code = code;
    }
    void SetDesc(const std::string &desc)
    {
        _status_code_desc = desc;
    }
    void MakeStatusLine()
    {
        _status_line = _http_version + BlankSep + std::to_string(_status_code) + BlankSep + _status_code_desc + LineSep;
    }
    void AddHeader(const std::string &header)
    {
        _resp_header.push_back(header + LineSep);
    }
    void AddContent(const std::string &content)
    {
        _resp_content = content;
    }
    std::string Serialize()
    {
        MakeStatusLine();
        std::string response_str = _status_line;
        for (auto &header : _resp_header)
        {
            response_str += header;
        }
        response_str += _resp_blank;
        response_str += _resp_content;

        return response_str;
    }
    ~HttpResponse() {}

private:
    std::string _status_line;
    std::vector<std::string> _resp_header;
    std::string _resp_blank;
    std::string _resp_content; // body

    // httpversion StatusCode StatusCodeDesc
    std::string _http_version;
    int _status_code;
    std::string _status_code_desc;
};

class Http
{
private:
    std::string GetMonthName(int month)
    {
        std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return months[month];
    }
    std::string GetWeekDayName(int day)
    {
        std::vector<std::string> weekdays = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return weekdays[day];
    }
    std::string ExpireTimeUseRfc1123(int t) // 秒级别的未来UTC时间
    {
        time_t timeout = time(nullptr) + t;
        struct tm *tm = gmtime(&timeout); // 这里不能用localtime，因为localtime是默认带了时区的. gmtime获取的就是UTC统一时间
        char timebuffer[1024];
        // 时间格式如: expires=Thu, 18 Dec 2024 12:00:00 UTC
        snprintf(timebuffer, sizeof(timebuffer), "%s, %02d %s %d %02d:%02d:%02d UTC",
                 GetWeekDayName(tm->tm_wday).c_str(),
                 tm->tm_mday,
                 GetMonthName(tm->tm_mon).c_str(),
                 tm->tm_year + 1900,
                 tm->tm_hour,
                 tm->tm_min,
                 tm->tm_sec);
        return timebuffer;
    }

public:
    Http(uint16_t port)
    {
        _tsvr = std::make_unique<TcpServer>(port, std::bind(&Http::HandlerHttp, this, std::placeholders::_1));
        _tsvr->Init();

        _session_manager = std::make_unique<SessionManager>();
    }
    std::string ProveCookieWrite() // 证明cookie能被写入浏览器
    {
        return "Set-Cookie: username=zhangsan;";
    }
    std::string ProveCookieTimeOut()
    {
        return "Set-Cookie: username=zhangsan; expires=" + ExpireTimeUseRfc1123(60) + ";"; // 让cookie 1min后过期
    }
    std::string ProvePath()
    {
        return "Set-Cookie: username=zhangsan; path=/a/b;";
    }
    std::string ProveSession(const std::string &session_id)
    {
        return "Set-Cookie: sessionid=" + session_id + ";";
    }
    std::string HandlerHttp(std::string request)
    {
        HttpRequest req;
        HttpResponse resp;

        req.Deserialize(request);
        req.Parse();
        // req.DebugHttp();
        // std::cout << req.Url() << std::endl;

        // 下面的代码就用来测试，如果你想更优雅，可以回调出去处理
        static int number = 0;
        if (req.Url() == "/login") // 用/login path向指定浏览器写入sessionid，并在服务器维护对应的session对象
        {
            std::string sessionid = req.SessionId();
            if (sessionid.empty()) // 说明历史没有登陆过
            {
                std::string user = "user-" + std::to_string(number++);
                session_ptr s = std::make_shared<Session>(user, "logined");
                std::string sessionid = _session_manager->AddSession(s);
                lg.LogMessage(Debug, "%s 被添加, sessionid是: %s\n", user.c_str(), sessionid.c_str());
                resp.AddHeader(ProveSession(sessionid));
            }
        }
        else
        {
            // 当浏览器在本站点任何路径中活跃，都会自动提交sessionid, 我们就能知道谁活跃了.
            std::string sessionid = req.SessionId();
            if (!sessionid.empty())
            {
                session_ptr s = _session_manager->GetSession(sessionid);
                // 这个地方有坑，一定要判断服务器端session对象是否存在，因为可能测试的时候
                // 浏览器还有历史sessionid，但是服务器重启之后，session对象没有了.
                if(s != nullptr)
                    lg.LogMessage(Debug, "%s 正在活跃.\n", s->_username.c_str());
                else
                    lg.LogMessage(Debug, "cookie : %s 已经过期, 需要清理\n", sessionid.c_str()); 
            }
        }

        resp.SetCode(200);
        resp.SetDesc("OK");
        resp.AddHeader("Content-Type: text/html");
        // resp.AddHeader(ProveCookieWrite()); //测试cookie被写入与自动提交
        // resp.AddHeader(ProveCookieTimeOut()); //测试过期时间的写入
        //  resp.AddHeader(ProvePath()); // 测试路径
        resp.AddContent("<html><h1>helloworld</h1></html>");
        return resp.Serialize();
    }
    void Run()
    {
        _tsvr->Start();
    }
    ~Http()
    {
    }

private:
    std::unique_ptr<TcpServer> _tsvr;
    std::unique_ptr<SessionManager> _session_manager;
};
