#pragma once

#include <memory>
#include <time.h>
#include <chrono>

namespace fatdog {

namespace detail {

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

std::chrono::system_clock::time_point now();
std::tm localtime(const std::time_t &time_tt);
std::tm localtime();

}

}