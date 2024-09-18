#ifndef __M_BIT_H__
#define __M_BIT_H__
#include "logger.hpp"

// ⽇志宏 & 全局接⼝设计
namespace log
{
    Logger::ptr getLogger(const std::string &name)
    {
        return loggerManager::getInstance().getLogger(name);
    }
    Logger::ptr rootLogger()
    {
        return loggerManager::getInstance().rootLogger();
    }

#define debug(fmt, ...) debug(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define info(fmt, ...) info(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define warn(fmt, ...) warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define error(fmt, ...) error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define fatal(fmt, ...) fatal(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_DEBUG(logger, fmt, ...) (logger)->debug(fmt, ##__VA_ARGS__)
#define LOG_INFO(logger, fmt, ...) (logger)->info(fmt, ##__VA_ARGS__)
#define LOG_WARN(logger, fmt, ...) (logger)->warn(fmt, ##__VA_ARGS__)
#define LOG_ERROR(logger, fmt, ...) (logger)->error(fmt, ##__VA_ARGS__)
#define LOG_FATAL(logger, fmt, ...) (logger)->fatal(fmt, ##__VA_ARGS__)

#define LOGD(fmt, ...) LOG_DEBUG(log::rootLogger(), fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) LOG_INFO(log::rootLogger(), fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) LOG_WARN(log::rootLogger(), fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) LOG_ERROR(log::rootLogger(), fmt, ##__VA_ARGS__)
#define LOGF(fmt, ...) LOG_FATAL(log::rootLogger(), fmt, ##__VA_ARGS__)

}

#endif
