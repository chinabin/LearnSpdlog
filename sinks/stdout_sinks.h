#pragma once

#include <cstdio>       // stdout stderr
#include <string>

#include "sink.h"

namespace fatdog {

class base_sink: public sink {
public:
    base_sink(FILE* file);
    ~base_sink() {}

    void log(const log_event& msg) override;
    void set_formatter(std::unique_ptr<formatter>&& fmter) override;
    void set_pattern(const std::string& pattern) override;
    void flush_now() override;

    bool should_log(LOG_LEVEL level);
    LOG_LEVEL get_level();
    void set_level(LOG_LEVEL level);
private:
    FILE* _file{nullptr};
};

class stdout_sink : public base_sink {
public:
    stdout_sink();

};

}