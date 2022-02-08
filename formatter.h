#pragma once

#include <string>
#include <vector>

#include "log_event.h"

namespace fatdog {

class format_item {
public:
    virtual std::string format(const log_event& msg) = 0;
};

class formatter {
public:
    formatter(const std::string& pattern);

    void set_pattern(const std::string& pattern);
    std::string format(const log_event& msg);

private:
    void parse();

private:
    std::string _pattern;
    std::vector<format_item*> _formatters;
};

}
