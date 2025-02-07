#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <unistd.h>
#include <unordered_map>

// 用来进行测试说明
class Session
{
public:
    Session(const std::string &username, const std::string &status)
    :_username(username), _status(status)
    {
        _create_time = time(nullptr); // 获取时间戳就行了，后面实际需要，就转化就转换一下
    }
    ~Session()
    {}
public:
    std::string _username;
    std::string _status;
    uint64_t _create_time;
    uint64_t _time_out; // 60*5
    std::string vip; // vip
    int active; // 
    std::string pos;
    //当然还可以再加任何其他信息，看你的需求
};

using session_ptr = std::shared_ptr<Session>;

class SessionManager
{
public:
    SessionManager()
    {
        srand(time(nullptr) ^ getpid());
    }
    std::string AddSession(session_ptr s)
    {
        uint32_t randomid = rand() + time(nullptr); // 随机数+时间戳，实际有形成sessionid的库，比如boost uuid库，或者其他第三方库等
        std::string sessionid = std::to_string(randomid);
        _sessions.insert(std::make_pair(sessionid, s));
        return sessionid;
    }
    session_ptr GetSession(const std::string sessionid)
    {
        if(_sessions.find(sessionid) == _sessions.end()) return nullptr;
        return _sessions[sessionid];
    }
    ~SessionManager()
    {}
private:
    std::unordered_map<std::string, session_ptr> _sessions;
};