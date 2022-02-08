#include "log_event.h"

namespace fatdog {

log_level::log_level(LOG_LEVEL level)
    :_level(level)
{}

std::string log_level::format() const
{
    switch (_level)
    {
    case LOG_LEVEL::LOG_LEVEL_DEBUG:
        return "DEBUG";
    case LOG_LEVEL::LOG_LEVEL_INFO:
        return "INFO";
    case LOG_LEVEL::LOG_LEVEL_WARN:
        return "WARN";
    case LOG_LEVEL::LOG_LEVEL_ERROR:
        return "ERROR";
    
    default:
        return "";
    }
}

log_event::log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc)
    :_msg(msg), _level(level), _loc(loc)
{}

}