cmake_minimum_required(VERSION 3.10)
project(fatdog)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(.)
include_directories(sinks)
include_directories(external)
include_directories(lib)

add_subdirectory(external/fmt EXCLUDE_FROM_ALL)

set(FATDOG_LOG_SRCS logger.cpp sinks/stdout_sinks.cpp formatter.cpp log_event.cpp)
add_library(fatdog_log SHARED ${FATDOG_LOG_SRCS})
target_link_libraries(fatdog_log fmt::fmt)      # ???

enable_testing()    # 加上这一句，才能 make test
add_subdirectory(test)