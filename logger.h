#pragma once

#include <vector>
#include <string>

#include "fmt/include/fmt/format.h"

#include <iostream>

#include "sink.h"
namespace fatdog {


using string_view = fmt::basic_string_view<char>;
using memory_buffer = fmt::basic_memory_buffer<char, 250>;

// logger 不保存 formatter ，formatter 是和 sink 绑定的，logger 拿了也没用
// level 可以保存一份，当一个消息过来的时候，首先 logger 判断一次，然后传给 sink 再判断一次
class logger {
public:
    logger(const std::string& logger_name);
    logger(const std::string& logger_name, std::unique_ptr<sink> s);

    void set_formatter(std::unique_ptr<formatter> formatter);

    void set_level(LOG_LEVEL level);
    LOG_LEVEL get_level() const;

    std::string name();

    void add_sink(std::unique_ptr<sink> s);



    // # 1
    template<typename... Args>
    void log(source_loc loc, LOG_LEVEL level, string_view fmt, Args&&... args)
    {
        log_(loc, level, fmt, std::forward<Args>(args)... );
    }

    // # 2 -> 1
    template<typename... Args>
    void log(LOG_LEVEL level, string_view fmt, Args&&... args)
    {
        log(source_loc{}, level, fmt, std::forward<Args>(args)... );
    }

    // # 3 -> 4
    template<typename T>
    void log(LOG_LEVEL level, const T &msg)
    {
        log(source_loc{}, level, msg);
    }

    // # 4 -> 1
    template<typename T>
    void log(source_loc loc, LOG_LEVEL level, const T &msg)
    {
        log(loc, level, "{}", msg);
    }

    // # 5 -> 3
    template<typename T>
    void trace(const T &msg)
    {
        log(LOG_LEVEL::LOG_LEVEL_TRACE, msg);
    }

    template<typename T>
    void debug(const T &msg)
    {
        log(LOG_LEVEL::LOG_LEVEL_DEBUG, msg);
    }

    template<typename T>
    void info(const T &msg)
    {
        log(LOG_LEVEL::LOG_LEVEL_INFO, msg);
    }

    template<typename T>
    void warn(const T &msg)
    {
        log(LOG_LEVEL::LOG_LEVEL_WARN, msg);
    }
    
    template<typename T>
    void error(const T &msg)
    {
        log(LOG_LEVEL::LOG_LEVEL_ERROR, msg);
    }

    template<typename T>
    void critical(const T &msg)
    {
        log(LOG_LEVEL::LOG_LEVEL_CRITICAL, msg);
    }


    // # 6 -> 2
    template<typename... Args>
    void trace(string_view fmt, Args &&... args)
    {
        log(LOG_LEVEL::LOG_LEVEL_TRACE, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(string_view fmt, Args &&... args)
    {
        log(LOG_LEVEL::LOG_LEVEL_DEBUG, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(string_view fmt, Args &&... args)
    {
        log(LOG_LEVEL::LOG_LEVEL_INFO, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(string_view fmt, Args &&... args)
    {
        log(LOG_LEVEL::LOG_LEVEL_WARN, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(string_view fmt, Args &&... args)
    {
        log(LOG_LEVEL::LOG_LEVEL_ERROR, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(string_view fmt, Args &&... args)
    {
        log(LOG_LEVEL::LOG_LEVEL_CRITICAL, fmt, std::forward<Args>(args)...);
    }

private:
    template<typename... Args>
    void log_(source_loc loc, LOG_LEVEL level, string_view fmt, Args&&... args)
    {
        memory_buffer buf;
        fmt::detail::vformat_to(buf, fmt, fmt::make_format_args(std::forward<Args>(args)...));
        buf.append(_eol);
        log_event event{std::string(buf.data(), buf.size()), level, loc, _logger_name};
        log_it(event);
    }

    void log_it(const log_event& msg)
    {
        for (auto& it : _sinks) {
            it->log(msg);
        }
    }

    std::unique_ptr<formatter> _formatter;
    std::unique_ptr<log_level> _level;
    std::vector<std::unique_ptr<sink>> _sinks;
    std::string _logger_name;
    string_view _eol{"\n"};
};

}