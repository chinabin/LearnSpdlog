#include "log_event.h"

#include "common_func.h"

namespace fatdog {

log_level::log_level(LOG_LEVEL level)
    :_level(level)
{}

std::string log_level::format() const
{
    switch (_level)
    {
    case LOG_LEVEL::LOG_LEVEL_TRACE:
        return "TRACE";
    case LOG_LEVEL::LOG_LEVEL_DEBUG:
        return "DEBUG";
    case LOG_LEVEL::LOG_LEVEL_INFO:
        return "INFO";
    case LOG_LEVEL::LOG_LEVEL_WARN:
        return "WARN";
    case LOG_LEVEL::LOG_LEVEL_ERROR:
        return "ERROR";
    case LOG_LEVEL::LOG_LEVEL_CRITICAL:
        return "CRITICAL";
    
    default:
        return "";
    }
}

log_event::log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc, const type::log_clock::time_point& ltime, const std::string& logger_name)
    :_msg(msg), _level(level), _loc(loc), _time(ltime), _logger_name(logger_name)
{}

log_event::log_event(const std::string& msg, LOG_LEVEL level, const source_loc& loc, const std::string& logger_name)
    :_msg(msg), _level(level), _loc(loc), _time(detail::now()), _logger_name(logger_name)
{}

}