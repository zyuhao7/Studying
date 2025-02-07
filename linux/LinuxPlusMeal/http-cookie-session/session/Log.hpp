#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum
{
    Debug = 0,
    Info,
    Warning,
    Error,
    Fatal
};

enum
{
    Screen = 10,
    OneFile,
    ClassFile
};

std::string LevelToString(int level)
{
    switch (level)
    {
    case Debug:
        return "Debug";
    case Info:
        return "Info";
    case Warning:
        return "Warning";
    case Error:
        return "Error";
    case Fatal:
        return "Fatal";
    default:
        return "Unknown";
    }
}

const int defaultstyle = Screen;
const std::string default_filename = "log.";
const std::string logdir = "log";

class Log
{
public:
    Log() : style(defaultstyle), filename(default_filename)
    {
        mkdir(logdir.c_str(), 0775);
    }
    void Enable(int sty) //
    {
        style = sty;
    }
    std::string TimeStampExLocalTime()
    {
        time_t currtime = time(nullptr);
        struct tm *curr = localtime(&currtime);
        char time_buffer[128];
        snprintf(time_buffer, sizeof(time_buffer), "%d-%d-%d %d:%d:%d",
                 curr->tm_year + 1900, curr->tm_mon + 1, curr->tm_mday,
                 curr->tm_hour, curr->tm_min, curr->tm_sec);
        return time_buffer;
    }
    void WriteLogToOneFile(const std::string &logname, const std::string &message)
    {
        umask(0);
        int fd = open(logname.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666);
        if(fd < 0) return;
        write(fd, message.c_str(), message.size());
        close(fd);
        // std::ofstream out(logname);
        // if (!out.is_open())
        //     return;
        // out.write(message.c_str(), message.size());
        // out.close();
    }
    void WriteLogToClassFile(const std::string &levelstr, const std::string &message)
    {
        std::string logname = logdir;
        logname += "/";
        logname += filename;
        logname += levelstr;
        WriteLogToOneFile(logname, message);
    }

    void WriteLog(const std::string &levelstr, const std::string &message)
    {
        switch (style)
        {
        case Screen:
            std::cout << message;
            break;
        case OneFile:
            WriteLogToClassFile("all", message);
            break;
        case ClassFile:
            WriteLogToClassFile(levelstr, message);
            break;
        default:
            break;
        }
    }
    void LogMessage(int level, const char *format, ...) // 类C的一个日志接口
    {
        char leftbuffer[1024];
        std::string levelstr = LevelToString(level);
        std::string currtime = TimeStampExLocalTime();
        std::string idstr = std::to_string(getpid());

        char rightbuffer[1024];
        va_list args; // char *, void *
        va_start(args, format);
        // args 指向了可变参数部分
        vsnprintf(rightbuffer, sizeof(rightbuffer), format, args);
        va_end(args); // args = nullptr;
        snprintf(leftbuffer, sizeof(leftbuffer), "[%s][%s][%s] ",
                 levelstr.c_str(), currtime.c_str(), idstr.c_str());

        std::string loginfo = leftbuffer;
        loginfo += rightbuffer;
        WriteLog(levelstr, loginfo);
    }
    // void operator()(int level, const char *format, ...)
    // {
    //     LogMessage(int level, const char *format, ...)
    // }
    ~Log() {}

private:
    int style;
    std::string filename;
};

Log lg;

class Conf
{
public:
    Conf()
    {
        lg.Enable(Screen);
    }
    ~Conf()
    {}
};

Conf conf;
