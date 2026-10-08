#include "sink.hpp"
#include "formatter.hpp"
#include <iostream>
#include <string>
#include <memory>
using namespace std;

int main()
{
    // Log message to be used in all tests
    std::string logger_name = "myh";
    logging::LogMsg msg(logger_name, "main.cc", 27, "Formatted log message test!", logging::LogLevel::value::INFO);

    // Test 1 : Default Formatter and StdoutSink - lpthread
    {
        logging::Formatter fmt;
        string str = fmt.format(msg); // Format the log message
        logging::LogSink::ptr stdout_sink = logging::SinkFactory::create<logging::StdoutSink>();
        stdout_sink->log(str.c_str(), str.size()); // Write to stdout
    }

    // Test 2: Custom Formatter with file sink
    // {
    //     logging::Formatter fmt("[%d{%Y-%m-%d %H:%M:%S}]%T[%t][%p][%c] %m%n"); // Custom pattern
    //     string str = fmt.format(msg);                                     // Format the log message with the custom pattern
    //     logging::LogSink::ptr file_sink = logging::SinkFactory::create<logging::FileSink>("test_log.txt");
    //     file_sink->log(str.c_str(), str.size()); // Write to file
    // }

    // Test 3: Rolling File Sink
    // {
    //     logging::Formatter fmt("[%d{%H:%M:%S}][%p] %m%n");                                                    // Another custom pattern
    //     string str = fmt.format(msg);                                                                     // Format the log message
    //     logging::LogSink::ptr roll_sink = logging::SinkFactory::create<logging::RollSink>("./logfile/roll_log_", 50); // Small max file size for testing
    //     for (int i = 0; i < 10086; ++i)
    //     {
    //         string test_str = "Log entry #" + std::to_string(i) + ": " + str;
    //         roll_sink->log(test_str.c_str(), test_str.size()); // Write several entries to trigger rolling
    //     }
    // }

    return 0;
}
