#include "sink.hpp"
#include "formatter.hpp"
#include <iostream>
#include <string>
#include <memory>
using namespace std;

int main()
{
    // Log message to be used in all tests
    // std::string logger_name = "myh";
    // log::LogMsg msg(logger_name, "main.cc", 27, "Formatted log message test!", log::LogLevel::value::INFO);

    // Test 1 : Default Formatter and StdoutSink -lpthread
    // {
    //     log::Formatter fmt;
    //     string str = fmt.format(msg); // Format the log message
    //     log::LogSink::ptr stdout_sink = log::SinkFactory::create<log::StdoutSink>();
    //     stdout_sink->log(str.c_str(), str.size()); // Write to stdout
    // }

    // Test 2: Custom Formatter with file sink
    // {
    //     log::Formatter fmt("[%d{%Y-%m-%d %H:%M:%S}]%T[%t][%p][%c] %m%n"); // Custom pattern
    //     string str = fmt.format(msg);                                     // Format the log message with the custom pattern
    //     log::LogSink::ptr file_sink = log::SinkFactory::create<log::FileSink>("test_log.txt");
    //     file_sink->log(str.c_str(), str.size()); // Write to file
    // }

    // Test 3: Rolling File Sink
    // {
    //     log::Formatter fmt("[%d{%H:%M:%S}][%p] %m%n");                                                    // Another custom pattern
    //     string str = fmt.format(msg);                                                                     // Format the log message
    //     log::LogSink::ptr roll_sink = log::SinkFactory::create<log::RollSink>("./logfile/roll_log_", 50); // Small max file size for testing
    //     for (int i = 0; i < 10086; ++i)
    //     {
    //         string test_str = "Log entry #" + std::to_string(i) + ": " + str;
    //         roll_sink->log(test_str.c_str(), test_str.size()); // Write several entries to trigger rolling
    //     }
    // }

    return 0;
}
