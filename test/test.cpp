#include "includes.h"
#include "logger.h"

#include "stdout_sinks.h"

TEST_CASE("a demo", "[demo]")
{
    std::cout << "hello, fatdog~" << std::endl;
    REQUIRE(1 == 1);
}

TEST_CASE("format", "[stdout_sink]")
{
    fatdog::formatter format("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    fatdog::log_event event{"hello, format\n", fatdog::LOG_LEVEL::LOG_LEVEL_INFO, {__FILE__, __LINE__, __FUNCTION__}};
    fatdog::stdout_sink sink;
    sink.set_formatter(&format);
    sink.log(event);
}

TEST_CASE("log", "[logger]")
{
    fatdog::logger log_msg;
    log_msg.log("hello, logger!\n");
}