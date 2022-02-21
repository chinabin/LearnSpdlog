#include "logger.h"
#include "stdout_sinks.h"
#include "common_func.h"

namespace fatdog {

logger::logger()
{
    auto new_formatter = detail::make_unique<formatter>("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    _formatter = std::move(new_formatter);
    auto new_level = detail::make_unique<log_level>(LOG_LEVEL::LOG_LEVEL_INFO);
    _level = std::move(new_level);
    auto new_sink = detail::make_unique<stdout_sink>();
    add_sink(std::move(new_sink));
}

logger::logger(std::unique_ptr<formatter> formatter, LOG_LEVEL level)
    :_formatter(std::move(formatter))
{
    auto new_level = detail::make_unique<log_level>(level);
    _level = std::move(new_level);
    auto new_sink = detail::make_unique<stdout_sink>();
    add_sink(std::move(new_sink));
}

logger::logger(std::unique_ptr<formatter> formatter)
    :_formatter(std::move(formatter))
{
    auto new_level = detail::make_unique<log_level>(LOG_LEVEL::LOG_LEVEL_INFO);
    _level = std::move(new_level);
    auto new_sink = detail::make_unique<stdout_sink>();
    add_sink(std::move(new_sink));
}

logger::logger(std::unique_ptr<log_level> level)
    :_level(std::move(level))
{
    auto new_formatter = detail::make_unique<formatter>("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    _formatter = std::move(new_formatter);
    auto new_sink = detail::make_unique<stdout_sink>();
    add_sink(std::move(new_sink));
}

logger::logger(const std::string& logger_name, std::unique_ptr<sink> s)
    :_logger_name(logger_name)
{
    auto new_formatter = detail::make_unique<formatter>("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    _formatter = std::move(new_formatter);
    auto new_level = detail::make_unique<log_level>(LOG_LEVEL::LOG_LEVEL_INFO);
    _level = std::move(new_level);
    _sinks.emplace_back(std::move(s));
}

void logger::set_formatter(std::unique_ptr<formatter> formatter)
{
    _formatter = std::move(formatter);
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

void logger::log(const std::string& msg)
{
    log_event event{msg, _level->_level, {__FILE__, __LINE__, __FUNCTION__}};
    for (auto& it : _sinks) {
        it->log(event);
    }
}

}