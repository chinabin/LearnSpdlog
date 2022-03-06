#pragma once

#include <memory>
#include <time.h>

#include "type.h"

namespace fatdog {

namespace detail {

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

type::log_clock::time_point now();
std::tm localtime(const std::time_t &time_tt);
std::tm localtime();

size_t thread_id();

template<typename T>
T time_fraction(type::log_clock::time_point tp)
{
    using std::chrono::duration_cast;
    using std::chrono::seconds;
    auto durations = tp.time_since_epoch();
    auto s = duration_cast<seconds>(durations);

    return duration_cast<T>(durations) - duration_cast<T>(s);
}

}

}