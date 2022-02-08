#include "logger.h"
#include "stdout_sinks.h"

namespace fatdog {

logger::logger()
{
    _formatter = new formatter("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    _level = new log_level(LOG_LEVEL::LOG_LEVEL_INFO);
    stdout_sink* s = new stdout_sink();
    s->set_formatter(_formatter);
    add_sink(s);
}

logger::logger(formatter* formatter, LOG_LEVEL level)
    :_formatter(formatter)
{
    _level = new log_level(level);
    stdout_sink* s = new stdout_sink();
    s->set_formatter(_formatter);
    add_sink(s);
}

logger::logger(formatter* formatter)
    :_formatter(formatter)
{
    _level = new log_level(LOG_LEVEL::LOG_LEVEL_INFO);
    stdout_sink* s = new stdout_sink();
    s->set_formatter(_formatter);
    add_sink(s);
}

logger::logger(log_level* level)
    :_level(level)
{
    _formatter = new formatter("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    stdout_sink* s = new stdout_sink();
    s->set_formatter(_formatter);
    add_sink(s);
}

void logger::set_formatter(formatter* formatter)
{
    _formatter = formatter;
}

formatter* logger::get_formatter()
{
    return _formatter;
}

void logger::set_level(LOG_LEVEL level)
{
    _level->_level = level;
}

LOG_LEVEL logger::get_level() const
{
    return _level->_level;
}

void logger::add_sink(sink* s)
{
    _sinks.emplace_back(s);
}

void logger::log(const std::string& msg)
{
    log_event event{msg, _level->_level, {__FILE__, __LINE__, __FUNCTION__}};
    for (auto& it : _sinks) {
        it->log(event);
    }
}

}