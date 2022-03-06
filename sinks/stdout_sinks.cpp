#include "stdout_sinks.h"
#include "common_func.h"

namespace fatdog {

base_sink::base_sink(FILE* file)
    :_file(file)
{
}

void base_sink::log(const log_event& msg)
{
    if (!_formatter) {
        auto new_formatter = detail::make_unique<formatter>("%+");
        _formatter = std::move(new_formatter);
    }
    // std::string log_msg = _formatter->format(msg);
    std::string log_msg = _formatter->format(msg);
    ::fwrite(log_msg.c_str(), sizeof(char), log_msg.size(), _file);
    ::fflush(_file);
}

void base_sink::set_formatter(std::unique_ptr<formatter>&& fmter)
{
    _formatter = std::move(fmter);
}

void base_sink::set_pattern(const std::string& pattern)
{
    _formatter = detail::make_unique<formatter>(pattern);
}

void base_sink::flush_now()
{
    ::fflush(_file);
}

bool base_sink::should_log(LOG_LEVEL level)
{
    if (_level > level) {
        return false;
    }
    return true;
}

LOG_LEVEL base_sink::get_level()
{
    return _level;
}

void base_sink::set_level(LOG_LEVEL level)
{
    _level = level;
}





stdout_sink::stdout_sink()
    :base_sink(stdout)
{}

}