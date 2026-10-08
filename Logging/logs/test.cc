#include "bitlog.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>

static int g_fail = 0;
#define CHECK(cond, name)                           \
    do                                              \
    {                                               \
        if (cond)                                   \
            std::cout << "[PASS] " << name << "\n"; \
        else                                        \
        {                                           \
            std::cout << "[FAIL] " << name << "\n"; \
            ++g_fail;                               \
        }                                           \
    } while (0)

static std::string readFile(const std::string &path)
{
    std::ifstream ifs(path, std::ios::binary);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

static size_t countLines(const std::string &s)
{
    size_t n = 0;
    for (char c : s)
        if (c == '\n')
            ++n;
    return n;
}

static size_t countFiles(const std::string &dir)
{
    DIR *d = opendir(dir.c_str());
    if (!d)
        return 0;
    size_t n = 0;
    struct dirent *e;
    while ((e = readdir(d)) != nullptr)
        if (e->d_name[0] != '.')
            ++n;
    closedir(d);
    return n;
}

static void test_formatter()
{
    std::string name = "fmt";
    logging::LogMsg msg(name, "f.cc", 12, std::string("hello"), logging::LogLevel::value::INFO);

    logging::Formatter def;
    std::string out = def.format(msg);
    CHECK(out.find("hello") != std::string::npos &&
              out.find("INFO") != std::string::npos &&
              out.find("f.cc:12") != std::string::npos,
          "formatter 默认格式含 payload/级别/文件行号");

    logging::Formatter custom("%m%n");
    CHECK(custom.format(msg) == "hello\n", "formatter 自定义格式 %m%n");
}

static void test_file_sink()
{
    std::string path = "/tmp/logtest_file.log";
    std::remove(path.c_str());
    {
        logging::FileSink sink(path);
        std::string d = "abc\n";
        sink.log(d.c_str(), d.size());
    }
    CHECK(readFile(path) == "abc\n", "FileSink 落地内容正确");
}

static void test_roll_sink()
{
    std::string dir = "/tmp/logtest_roll";
    std::system(("rm -rf " + dir).c_str());
    {
        logging::RollSink sink(dir + "/r_", 100); // 100B 上限
        std::string d(31, 'a');
        d += '\n';
        for (int i = 0; i < 20; ++i)
            sink.log(d.c_str(), d.size());
    }
    CHECK(countFiles(dir) >= 4, "RollSink 超限滚动出多个文件");
}

static void test_level_filter()
{
    std::string path = "/tmp/logtest_lvl.log";
    std::remove(path.c_str());
    {
        logging::LocalLoggerBuilder lb;
        lb.buildLoggerName("lvl");
        lb.buildFormatter("%p:%m%n");
        lb.buildSink<logging::FileSink>(path);
        lb.buildLoggerLevel(logging::LogLevel::value::WARN);
        auto lp = lb.build();
        lp->info("i1"); // 低于 WARN，应被抑制
        lp->warn("w1"); // 应保留
        lp->setLevel(logging::LogLevel::value::DEBUG);
        lp->info("i2"); // 运行时放宽级别后应保留
    }
    std::string c = readFile(path);
    CHECK(c.find("i1") == std::string::npos &&
              c.find("w1") != std::string::npos &&
              c.find("i2") != std::string::npos,
          "级别过滤与运行时 setLevel");
}

static void test_async_drain()
{
    std::string path = "/tmp/logtest_async.log";
    std::remove(path.c_str());
    {
        logging::LocalLoggerBuilder lb;
        lb.buildLoggerName("as");
        lb.buildFormatter("%m%n");
        lb.buildSink<logging::FileSink>(path);
        lb.buildLoggerType(logging::Logger::Type::LOGGER_ASYNC);
        auto lp = lb.build();
        for (int i = 0; i < 500; ++i)
            lp->info("line %d", i);
    } // lp 析构 -> looper 停止并排空
    CHECK(countLines(readFile(path)) == 500, "AsyncLogger 析构时排空队列");
}

int main()
{
    test_formatter();
    test_file_sink();
    test_roll_sink();
    test_level_filter();
    test_async_drain();

    if (g_fail == 0)
        std::cout << "ALL PASS\n";
    else
        std::cout << g_fail << " TEST(S) FAILED\n";
    return g_fail == 0 ? 0 : 1;
}
