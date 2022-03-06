cmake_minimum_required(VERSION 3.10)
project(fatdog)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(.)
include_directories(sinks)
include_directories(external)

link_directories(lib)

add_subdirectory(external/fmt EXCLUDE_FROM_ALL)

set(FATDOG_LOG_SRCS logger.cpp sinks/stdout_sinks.cpp formatter.cpp log_event.cpp registry.cpp fatdog.cpp common_func.cpp)
add_library(fatdog_log SHARED ${FATDOG_LOG_SRCS})
set(COMMON_LINK pthread rt dl)
target_link_libraries(fatdog_log libfmt.so)      # ???
set_target_properties(${bifexe} PROPERTIES LINK_FLAGS "-fPIC,-Wl,-rpath,'$ORIGIN'")

enable_testing()    # 加上这一句，才能 make test
add_subdirectory(test)

add_subdirectory(bench)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE fatdog_log)
