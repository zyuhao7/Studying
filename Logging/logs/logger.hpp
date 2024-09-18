#ifndef __M_LOG_H__
#define __M_LOG_H__
#include "util.hpp"
#include "level.hpp"
#include "message.hpp"
#include "formatter.hpp"
#include "sink.hpp"
#include "looper.hpp"
#include <vector>
#include <list>
#include <atomic>
#include <unordered_map>
#include <cstdarg>
#include <type_traits>

// ⽇志器类(Logger)设计（建造者模式）
namespace log
{
    class SyncLogger;
    class AsyncLogger;
    class Logger
    {
    public:
        enum class Type
        {
            LOGGER_SYNC = 0,
            LOGGER_ASYNC
        };
        using ptr = std::shared_ptr<Logger>;
        Logger(const std::string &name,
               Formatter::ptr formatter,
               std::vector<LogSink::ptr> &sinks,
               LogLevel::value level = LogLevel::value::DEBUG) : _name(name), _level(level), _formatter(formatter),
                                                                 _sinks(sinks.begin(), sinks.end())
        {
        }
        std::string loggerName() { return _name; }
        LogLevel::value loggerLevel() { return _level; }
        void debug(const char *file, size_t line, const char *fmt, ...)
        {
            if (shouldLog(LogLevel::value::DEBUG) == false)
            {
                return;
            }
            va_list al;
            va_start(al, fmt);
            log(LogLevel::value::DEBUG, file, line, fmt, al);
            va_end(al);
        }
        void info(const char *file, size_t line, const char *fmt, ...)
        {
            if (shouldLog(LogLevel::value::INFO) == false)
                return;
            va_list al;
            va_start(al, fmt);
            log(LogLevel::value::INFO, file, line, fmt, al);
            va_end(al);
        }
        void warn(const char *file, size_t line, const char *fmt, ...)
        {
            if (shouldLog(LogLevel::value::WARN) == false)
                return;
            va_list al;
            va_start(al, fmt);
            log(LogLevel::value::WARN, file, line, fmt, al);
            va_end(al);
        }
        void error(const char *file, size_t line, const char *fmt, ...)
        {
            if (shouldLog(LogLevel::value::ERROR) == false)
                return;
            va_list al;
            va_start(al, fmt);
            log(LogLevel::value::ERROR, file, line, fmt, al);
            va_end(al);
        }
        void fatal(const char *file, size_t line, const char *fmt, ...)
        {
            if (shouldLog(LogLevel::value::FATAL) == false)
                return;
            va_list al;
            va_start(al, fmt);
            log(LogLevel::value::FATAL, file, line, fmt, al);
            va_end(al);
        }

    public:
        class Builder
        {
        public:
            using ptr = std::shared_ptr<Builder>;

            Builder() : _level(LogLevel::value::DEBUG),
                        _logger_type(Logger::Type::LOGGER_SYNC) {}

            void buildLoggerName(const std::string &name) { _logger_name = name; }
            void buildLoggerLevel(LogLevel::value level) { _level = level; }
            void buildLoggerType(Logger::Type type) { _logger_type = type; }
            void buildFormatter(const std::string pattern) { _formatter = std::make_shared<Formatter>(pattern); }
            void buildFormatter(const Formatter::ptr &formatter) { _formatter = formatter; }

            template <typename SinkType, typename... Args>
            void buildSink(Args &&...args)
            {
                auto sink = SinkFactory::create<SinkType>(std::forward<Args>(args)...);
                _sinks.push_back(sink);
            }
            virtual Logger::ptr build() = 0;

        protected:
            Logger::Type _logger_type;
            std::string _logger_name;
            LogLevel::value _level;
            Formatter::ptr _formatter;
            std::vector<LogSink::ptr> _sinks;
        };

    protected:
        bool shouldLog(LogLevel::value level) { return level >= _level; }
        void log(LogLevel::value level, const char *file, size_t line, const char *fmt, va_list al)
        {
            char *buf;
            std::string msg;
            int len = vasprintf(&buf, fmt, al);
            if (len < 0)
            {
                msg = "格式化日志消息失败！！";
            }
            else
            {
                msg.assign(buf, len);
                free(buf);
            }
            // LogMsg(name, file, line, payload, level)
            LogMsg lm(_name, file, line, std::move(msg), level);
            std::stringstream ss;
            _formatter->format(ss, lm);
            logIt(std::move(ss.str()));
        }
        virtual void logIt(const std::string &msg) = 0;

    protected:
        std::mutex _mutex;
        std::string _name;
        Formatter::ptr _formatter;
        std::atomic<LogLevel::value> _level;
        std::vector<LogSink::ptr> _sinks;
    };

    class SyncLogger : public Logger
    {
    public:
        using ptr = std::shared_ptr<SyncLogger>;
        SyncLogger(const std::string &name,
                   Formatter::ptr formatter,
                   std::vector<LogSink::ptr> &sinks,
                   LogLevel::value level = LogLevel::value::DEBUG) : Logger(name, formatter, sinks, level)
        {
            std::cout << LogLevel::toString(level) << " 同步日志器: " << name << "创建成功...\n";
        }

    private:
        virtual void logIt(const std::string &msg)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            if (_sinks.empty())
            {
                return;
            }
            for (auto &it : _sinks)
            {
                it->log(msg.c_str(), msg.size());
            }
        }
    };

    class AsyncLogger : public Logger
    {
    public:
        using ptr = std::shared_ptr<AsyncLogger>;
        AsyncLogger(const std::string &name,
                    Formatter::ptr formatter,
                    std::vector<LogSink::ptr> &sinks,
                    LogLevel::value level = LogLevel::value::DEBUG) : Logger(name, formatter, sinks, level),
                                                                      _looper(std::make_shared<AsyncLooper>(std::bind(&AsyncLogger::backendLogIt, this, std::placeholders::_1)))
        {
            std::cout << LogLevel::toString(level) << "异步日志器: " << name << "创建成功...\n";
        }

    protected:
        virtual void logIt(const std::string &msg)
        {
            _looper->push(msg);
        }
        void backendLogIt(Buffer &msg)
        {
            if (_sinks.empty())
            {
                return;
            }
            for (auto &it : _sinks)
            {
                it->log(msg.begin(), msg.readAbleSize());
            }
        }

    protected:
        AsyncLooper::ptr _looper;
    };

    class LocalLoggerBuilder : public Logger::Builder
    {
    public:
        virtual Logger::ptr build()
        {
            if (_logger_name.empty())
            {
                std::cout << "日志器名称不能为空！！";
                abort();
            }
            if (_formatter.get() == nullptr)
            {
                std::cout << "当前日志器：" << _logger_name << " 未检测到日志格式，默认设置为[ %d{%H:%M:%S}%T%t%T[%p]%T[%c]%T%f:%l%T%m%n ]!\n";
                _formatter = std::make_shared<Formatter>();
            }
            if (_sinks.empty())
            {
                std::cout << "当前日志器：" << _logger_name << " 未检测到落地方向，默认设置为标准输出!\n";
                _sinks.push_back(std::make_shared<StdoutSink>());
            }

            Logger::ptr lp;
            if (_logger_type == Logger::Type::LOGGER_ASYNC)
            {
                lp = std::make_shared<AsyncLogger>(_logger_name, _formatter, _sinks, _level);
            }
            else
            {
                lp = std::make_shared<SyncLogger>(_logger_name, _formatter, _sinks, _level);
            }
            return lp;
        }
    };

    // 单例⽇志器管理类设计（单例模式)
    class loggerManager
    {
    private:
        std::mutex _mutex;
        Logger::ptr _root_logger; // 默认日志器.
        std::unordered_map<std::string, Logger::ptr> _loggers;

    private:
        loggerManager()
        {
            std::unique_ptr<LocalLoggerBuilder> slb(new LocalLoggerBuilder());
            slb->buildLoggerName("root");
            slb->buildLoggerType(Logger::Type::LOGGER_SYNC);
            _root_logger = slb->build();
            _loggers.insert(std::make_pair("root", _root_logger));
        }

        loggerManager(const loggerManager &) = delete;
        loggerManager &operator=(const loggerManager &) = delete;

    public:
        static loggerManager &getInstance()
        {
            static loggerManager lm;
            return lm;
        }
        bool hasLogger(const std::string &name)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            auto it = _loggers.find(name);
            if (it == _loggers.end())
            {
                return false;
            }
            return true;
        }
        void addLogger(const std::string &name, const Logger::ptr logger)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _loggers.insert(std::make_pair(name, logger));
        }
        Logger::ptr getLogger(const std::string &name)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            auto it = _loggers.find(name);
            if (it == _loggers.end())
            {
                return Logger::ptr();
            }
            return it->second;
        }
        Logger::ptr rootLogger()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            return _root_logger;
        }
    };

    class GlobalLoggerBuilder : public Logger::Builder
    {
    public:
        virtual Logger::ptr build()
        {
            if (_logger_name.empty())
            {
                std::cout << "日志器名称不能为空！！";
                abort();
            }
            assert(loggerManager::getInstance().hasLogger(_logger_name) == false);

            if (_formatter.get() == nullptr)
            {
                std::cout << "当前日志器：" << _logger_name << " 未检测到日志格式，默认设置为[ %d{%H:%M:%S}%T%t%T[%p]%T[%c]%T%f:%l%T%m%n ]!\n";
                _formatter = std::make_shared<Formatter>();
            }
            if (_sinks.empty())
            {
                std::cout << "当前日志器：" << _logger_name << " 未检测到落地方向，默认设置为标准输出!\n";
                _sinks.push_back(std::make_shared<StdoutSink>());
            }
            Logger::ptr lp;
            if (_logger_type == Logger::Type::LOGGER_ASYNC)
            {
                lp = std::make_shared<AsyncLogger>(_logger_name, _formatter, _sinks, _level);
            }
            else
            {
                lp = std::make_shared<SyncLogger>(_logger_name, _formatter, _sinks, _level);
            }
            loggerManager::getInstance().addLogger(_logger_name, lp);
            return lp;
        }
    };
}
#endif