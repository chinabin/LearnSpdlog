#pragma once

#include <vector>
#include <string>

#include "sink.h"
namespace fatdog {

class logger {
public:
    logger();
    logger(std::unique_ptr<formatter> formatter, LOG_LEVEL level);
    logger(std::unique_ptr<formatter> formatter);
    logger(std::unique_ptr<log_level> level);
    logger(const std::string& _logger_name, std::unique_ptr<sink> s);

    void set_formatter(std::unique_ptr<formatter> formatter);

    void set_level(LOG_LEVEL level);
    LOG_LEVEL get_level() const;

    void add_sink(std::unique_ptr<sink> s);

    void log(const std::string& msg);
private:
    std::unique_ptr<formatter> _formatter;
    std::unique_ptr<log_level> _level;
    std::vector<std::unique_ptr<sink>> _sinks;
    std::string _logger_name;
};

}