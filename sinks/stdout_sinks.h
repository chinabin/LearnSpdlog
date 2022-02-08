#pragma once

#include <cstdio>       // stdout stderr
#include <string>

#include "sink.h"

namespace fatdog {

class stdout_sink: public sink {
public:
    stdout_sink();

    void log(const log_event& msg) override;
private:
    FILE* _file{stdout};
};

}