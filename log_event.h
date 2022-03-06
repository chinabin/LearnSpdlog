#pragma once

#include <string>

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


struct log_time 
{
    std::string _time;
};

struct extra_info
{
    int _thread_id = -1;
};



class log_event {
public:
    log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc, const log_time& ltime, const std::string& logger_name, const extra_info& einfo);
    log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc, const std::string& logger_name);

public:
    std::string _msg;
    std::string _logger_name;
    log_level _level;
    source_loc _loc;
    log_time _time;
    extra_info _extra_info;
};

}