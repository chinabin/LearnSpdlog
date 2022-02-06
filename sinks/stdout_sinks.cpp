#include "stdout_sinks.h"

namespace fatdog {

namespace sinks {

stdout_sink::stdout_sink()
{}

void stdout_sink::log(const std::string& msg)
{
    ::fwrite(msg.c_str(), sizeof(char), msg.size(), _file);
    ::fflush(_file);
}

}

}