cmake_minimum_required(VERSION 3.10)
project(fatdog_utests LANGUAGES CXX)

set(FATDOG_UTESTS_SOURCES
    test.cpp
    main.cpp)

enable_testing()
add_executable(fatdog_utests ${FATDOG_UTESTS_SOURCES})
target_link_libraries(fatdog_utests PRIVATE fatdog_log)

# https://cmake.org/cmake/help/v3.8/command/add_test.html#command:add_test
# add_test(NAME TestName COMMAND ExecutableToRun arg1 arg2 ...)
add_test(NAME test_me COMMAND fatdog_utests)

# https://cmake.org/cmake/help/v3.8/manual/cmake-properties.7.html#test-properties
# set_tests_properties(test1 [test2...] PROPERTIES prop1 value1 prop2 value2)
set_tests_properties(test_me PROPERTIES RUN_SERIAL ON)

