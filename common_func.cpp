#include "common_func.h"

namespace fatdog {

namespace detail {
std::chrono::system_clock::time_point now()
{
    return std::chrono::system_clock::now();
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

}

}