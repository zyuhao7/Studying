#ifndef __M_SINK_H__
#define __M_SINK_H__
#include "util.hpp"
#include "message.hpp"
#include "formatter.hpp"
#include <memory>
#include <mutex>

// 日志落地类

namespace log
{
    class LogSink
    {
    public:
        using ptr = std::shared_ptr<LogSink>;
        LogSink() {}
        virtual ~LogSink() {}
        // 加锁后调用子类 write 实现，保证多线程落地安全
        void log(const char *data, size_t len)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            write(data, len);
        }

    protected:
        virtual void write(const char *data, size_t len) = 0;

    private:
        std::mutex _mutex;
    };

    class StdoutSink : public LogSink
    {
    public:
        using ptr = std::shared_ptr<StdoutSink>;

    protected:
        void write(const char *data, size_t len) override
        {
            std::cout.write(data, len);
        }
    };

    class FileSink : public LogSink
    {
    public:
        using ptr = std::shared_ptr<FileSink>;
        FileSink(const std::string &filename)
            : _filename(filename)
        {
            util::file::create_directory(util::file::path(filename));
            _ofs.open(_filename, std::ios::binary | std::ios::app);
            assert(_ofs.is_open());
        }

        const std::string &file()
        {
            return _filename;
        }

    protected:
        void write(const char *data, size_t len) override
        {
            _ofs.write((const char *)data, len);
            if (_ofs.good() == false)
            {
                std::cout << "日志输出文件失败! " << std::endl;
            }
        }

    private:
        std::string _filename;
        std::ofstream _ofs;
    };

    class RollSink : public LogSink
    {
    public:
        using ptr = std::shared_ptr<RollSink>;
        RollSink(const std::string &basename, size_t max_fsize)
            : _basename(basename),
              _max_fsize(max_fsize),
              _cur_fsize(0)
        {
            util::file::create_directory(util::file::path(basename));
        }

    protected:
        void write(const char *data, size_t len) override
        {
            initLogFile();
            _ofs.write(data, len);
            if (_ofs.good() == false)
            {
                std::cout << "日志输出文件失败! \n";
            }
            _cur_fsize += len;
        }

    private:
        void initLogFile()
        {
            if (_ofs.is_open() == false || _cur_fsize >= _max_fsize)
            {
                _ofs.close();
                std::string name = createFilename();
                _ofs.open(name, std::ios::binary | std::ios::app);
                assert(_ofs.is_open());
                // createFilename 保证是全新文件，尺寸从 0 起算
                _cur_fsize = 0;
                return;
            }
            return;
        }

        std::string createFilename()
        {
            time_t t = time(NULL);
            struct tm lt;
            localtime_r(&t, &lt);
            std::stringstream ss;
            ss << _basename;
            ss << lt.tm_year + 1900;
            ss << lt.tm_mon + 1;
            ss << lt.tm_mday;
            ss << lt.tm_hour;
            ss << lt.tm_min;
            ss << lt.tm_sec;
            // 秒级时间戳同一秒内可能重复，追加序号保证文件名唯一
            std::string base = ss.str();
            std::string name = base + ".log";
            int idx = 1;
            while (util::file::exists(name))
            {
                name = base + "_" + std::to_string(idx++) + ".log";
            }
            return name;
        }
        std::string _basename;
        std::ofstream _ofs;
        size_t _max_fsize;
        size_t _cur_fsize;
    };

    class SinkFactory
    {
    public:
        template <typename SinkType, typename... Args>
        static LogSink::ptr create(Args &&...args)
        {
            return std::make_shared<SinkType>(std::forward<Args>(args)...);
        }
    };
}

#endif