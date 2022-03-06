#include "common_func.h"

#include <sys/syscall.h>    // for SYS_XX
#include <unistd.h>         // for syscall

namespace fatdog {

namespace detail {

type::log_clock::time_point now()
{
    return type::log_clock::now();
}

std::tm localtime(const std::time_t &time_tt)
{
    std::tm tm;
    ::localtime_r(&time_tt, &tm);
    return tm;
}

std::tm localtime()
{
    std::time_t now_t = ::time(nullptr);
    return localtime(now_t);
}

size_t thread_id()
{
    return static_cast<size_t>(::syscall(SYS_gettid));
}

}

}