#pragma once

#include <cstdio>       // stdout stderr
#include <string>

#include "log_event.h"
#include "formatter.h"

namespace fatdog {

class sink {
public:
    sink() = default;

    virtual void log(const log_event& msg) = 0;
    void set_formatter(std::unique_ptr<formatter> fmter) { _formatter = std::move(fmter); }
protected:
    std::unique_ptr<formatter> _formatter;
};

}