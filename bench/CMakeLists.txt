# Copyright(c) 2019 spdlog authors Distributed under the MIT License (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.10)
project(fatdog_bench CXX)

find_package(Threads REQUIRED)
find_package(benchmark CONFIG)
if(NOT benchmark_FOUND)
    message(STATUS "Using CMake Version ${CMAKE_VERSION}")
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
        # User can fetch googlebenchmark
        message(STATUS "Downloading GoogleBenchmark")
        include(FetchContent)

        # disable tests  
        set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")        
        # Do not build and run googlebenchmark tests
        FetchContent_Declare(googlebenchmark GIT_REPOSITORY https://github.com/google/benchmark.git GIT_TAG v1.6.0)
        FetchContent_MakeAvailable(googlebenchmark)
    else()
        message(FATAL_ERROR "GoogleBenchmark is missing. Use CMake >= 3.11 or download it")
    endif()
endif()

add_executable(bench bench.cpp)
set(COMMON_LINK pthread rt dl fatdog_log)
target_link_libraries(bench PRIVATE benchmark::benchmark ${COMMON_LINK})
set_target_properties(bench PROPERTIES LINK_FLAGS "-Wl,-rpath,'$ORIGIN'")

