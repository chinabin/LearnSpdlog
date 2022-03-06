#pragma once

#include <string>
#include "common_func.h"
#include "type.h"

namespace fatdog {

enum LOG_LEVEL
{
    LOG_LEVEL_NONE,
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL,
    LOG_LEVEL_END,
};

struct log_level {
    log_level(LOG_LEVEL level);
    std::string format() const;

    LOG_LEVEL _level;
};



struct source_loc
{
    source_loc() = default;
    source_loc(const std::string& filename_in, int line_in, const std::string& funcname_in)
        : _filename(filename_in)
        , _line(line_in)
        , _funcname(funcname_in)
    {}

    bool empty() const
    {
        return _line == 0;
    }
    std::string _filename;
    int _line{0};
    std::string _funcname;
};

class log_event {
public:
    log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc, const type::log_clock::time_point& ltime, const std::string& logger_name);
    log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc, const std::string& logger_name);

public:
    std::string _msg;
    std::string _logger_name;
    log_level _level;
    source_loc _loc;
    type::log_clock::time_point _time;

    size_t _thread_id = detail::thread_id();
};

}