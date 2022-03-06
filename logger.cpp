#include "logger.h"
#include "stdout_sinks.h"
#include "common_func.h"

namespace fatdog {

logger::logger(const std::string& logger_name)
    :_logger_name(logger_name)
{
    _level = detail::make_unique<log_level>(LOG_LEVEL::LOG_LEVEL_INFO);
    add_sink(detail::make_unique<stdout_sink>());
}

logger::logger(const std::string& logger_name, std::unique_ptr<sink> s)
    :_logger_name(logger_name)
{
    _level = detail::make_unique<log_level>(LOG_LEVEL::LOG_LEVEL_INFO);
    _sinks.emplace_back(std::move(s));
}

void logger::set_formatter(std::unique_ptr<formatter> fmter)
{
    for (auto const &it : _sinks) {
        it->set_formatter(fmter->clone());
    }
}

void logger::set_level(LOG_LEVEL level)
{
    _level->_level = level;
}

LOG_LEVEL logger::get_level() const
{
    return _level->_level;
}

void logger::add_sink(std::unique_ptr<sink> s)
{
    _sinks.emplace_back(std::move(s));
}


std::string logger::name()
{
    return _logger_name;
}


}