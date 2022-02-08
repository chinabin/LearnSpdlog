#pragma once

#include <string>

namespace fatdog {

enum LOG_LEVEL
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
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
    log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc);

public:
    std::string _msg;
    log_level _level;
    source_loc _loc;
};

}