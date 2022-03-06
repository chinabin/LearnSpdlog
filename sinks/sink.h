#pragma once

#include <cstdio>       // stdout stderr
#include <string>

#include "log_event.h"
#include "formatter.h"

namespace fatdog {

class sink {
public:
    sink() = default;

    virtual void log(const log_event& msg) = 0;
    virtual void set_formatter(std::unique_ptr<formatter>&& fmter) = 0;
    virtual void set_pattern(const std::string&) = 0;
    virtual void flush_now() = 0;

    bool should_log(LOG_LEVEL level);
    LOG_LEVEL get_level();
    void set_level(LOG_LEVEL level);

protected:
    LOG_LEVEL _level{LOG_LEVEL::LOG_LEVEL_INFO};
    std::unique_ptr<formatter> _formatter;
};

}