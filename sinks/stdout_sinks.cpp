#include "stdout_sinks.h"
#include "common_func.h"

namespace fatdog {

stdout_sink::stdout_sink()
{
}

void stdout_sink::log(const log_event& msg)
{
    if (!_formatter) {
        auto new_formatter = detail::make_unique<formatter>("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
        _formatter = std::move(new_formatter);
    }
    std::string log_msg = _formatter->format(msg);
    ::fwrite(log_msg.c_str(), sizeof(char), log_msg.size(), _file);
    ::fflush(_file);
}

}