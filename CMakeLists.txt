cmake_minimum_required(VERSION 3.10)
project(fatdog)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(sinks)

set(FATDOG_LOG_SRCS sinks/stdout_sinks.cpp)
add_library(fatdog_log SHARED ${FATDOG_LOG_SRCS})

enable_testing()    # 加上这一句，才能 make test
add_subdirectory(test)