#include "stdout_sinks.h"
#include "common_func.h"

namespace fatdog {

stdout_sink::stdout_sink()
{
}

void stdout_sink::log(const log_event& msg)
{
    if (!_formatter) {
        auto new_formatter = detail::make_unique<formatter>("%+");
        _formatter = std::move(new_formatter);
    }
    // std::string log_msg = _formatter->format(msg);
    std::string log_msg = "\033[32m";
    log_msg += _formatter->format(msg);
    log_msg += "\033[m";
    ::fwrite(log_msg.c_str(), sizeof(char), log_msg.size(), _file);
    ::fflush(_file);
}

void stdout_sink::set_formatter(std::unique_ptr<formatter>&& fmter)
{
    _formatter = std::move(fmter);
}

void stdout_sink::set_pattern(const std::string& pattern)
{
    _formatter = detail::make_unique<formatter>(pattern);
}

void stdout_sink::flush_now()
{
    ::fflush(_file);
}

bool stdout_sink::should_log(LOG_LEVEL level)
{
    if (_level > level) {
        return false;
    }
    return true;
}

LOG_LEVEL stdout_sink::get_level()
{
    return _level;
}

void stdout_sink::set_level(LOG_LEVEL level)
{
    _level = level;
}


}