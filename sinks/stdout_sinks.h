#pragma once

#include <cstdio>       // stdout stderr
#include <string>

namespace fatdog {

namespace sinks {

class stdout_sink {
public:
    explicit stdout_sink();

    void log(const std::string& msg);
private:
    FILE* _file = stdout;
};

}

}