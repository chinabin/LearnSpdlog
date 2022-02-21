#include "includes.h"
#include "logger.h"
#include "common_func.h"
#include "synchronous_factory.h"
#include "stdout_sinks.h"

TEST_CASE("a demo", "[demo]")
{
    std::cout << "hello, fatdog~" << std::endl;
    REQUIRE(1 == 1);
}

TEST_CASE("format", "[stdout_sink]")
{
    auto new_formatter = fatdog::detail::make_unique<fatdog::formatter>("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
    fatdog::log_event event{"hello, format\n", fatdog::LOG_LEVEL::LOG_LEVEL_INFO, {__FILE__, __LINE__, __FUNCTION__}};
    fatdog::stdout_sink sink;
    sink.set_formatter(std::move(new_formatter));
    sink.log(event);
}

TEST_CASE("log", "[logger]")
{
    fatdog::logger log_msg;
    log_msg.log("hello, logger!\n");
}

TEST_CASE("factory", "[synchronous_factory]")
{
    std::string logger_name = "test";
    auto new_logger = fatdog::synchronous_factory::create<fatdog::stdout_sink>(logger_name);
    new_logger->log("hello, factory!\n");
}