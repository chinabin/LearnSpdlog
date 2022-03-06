#pragma once

#include <string>
#include <memory>

#include "logger.h"
#include "synchronous_factory.h"
#include "registry.h"

namespace fatdog {

using default_factory = synchronous_factory;

// C++ Primer 16.4.3
template<typename Sink, typename... SinkArgs>
std::shared_ptr<logger> create(std::string logger_name, SinkArgs&&... sink_args)
{
    return default_factory::create(logger_name, std::forward<SinkArgs>(sink_args)...);
}

void initialize_logger(std::shared_ptr<logger> new_logger);

std::shared_ptr<logger> get(const std::string& logger_name);

void set_formatter(std::unique_ptr<formatter> fmter);
void set_pattern(const std::string& pattern);

void set_level(LOG_LEVEL lvl);

void register_logger(std::shared_ptr<logger> new_logger);
void drop(const std::string& logger_name);
void drop_all();

void set_automatic_registration(bool v);

std::shared_ptr<logger> default_logger();
logger* default_logger_raw();
void set_default_logger(std::unique_ptr<logger> lgger);

void log();

}