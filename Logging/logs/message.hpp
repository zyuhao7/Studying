#ifndef __M_MSG_H__
#define __M_MSG_H__
#include "util.hpp"
#include "level.hpp"
#include <thread>
#include <memory>

namespace log
{
    struct LogMsg
    {
        using ptr = std::shared_ptr<LogMsg>;
        size_t _line;           // 行号
        size_t _ctime;          // 时间
        std::thread::id _tid;   // 线程 ID
        std::string _name;      // 日志器名称
        std::string _file;      // 日志名
        std::string _payload;   // 日志消息
        LogLevel::value _level; // 日志等级
        LogMsg(std::string &name, std::string file, size_t line, std::string &&payload, LogLevel::value level)
            : _name(name),
              _file(file),
              _payload(std::move(payload)),
              _level(level),
              _line(line),
              _ctime(util::data::now()),
              _tid(std::this_thread::get_id())
        {
            std::cout << "构造 msg \n";
        }
        ~LogMsg()
        {
            std::cout << "析构 msg \n";
        }
    };
}
#endif