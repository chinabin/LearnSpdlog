#pragma once

#include <vector>
#include "sink.h"
namespace fatdog {

class logger {
public:
    logger();
    logger(formatter* formatter, LOG_LEVEL level);
    logger(formatter* formatter);
    logger(log_level* level);

    void set_formatter(formatter* formatter);
    formatter* get_formatter();

    void set_level(LOG_LEVEL level);
    LOG_LEVEL get_level() const;

    void add_sink(sink* s);

    void log(const std::string& msg);
private:
    formatter* _formatter{nullptr};
    log_level* _level{nullptr};
    std::vector<sink*> _sinks;
};

}