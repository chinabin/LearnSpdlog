#include "stdout_sinks.h"

namespace fatdog {

stdout_sink::stdout_sink()
{
}

void stdout_sink::log(const log_event& msg)
{
    if (!_formatter) {
        _formatter = new formatter("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    }
    std::string log_msg = _formatter->format(msg);
    ::fwrite(log_msg.c_str(), sizeof(char), log_msg.size(), _file);
    ::fflush(_file);
}

}