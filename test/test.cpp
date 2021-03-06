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
    fatdog::log_event event{"hello, format", fatdog::LOG_LEVEL::LOG_LEVEL_INFO, {__FILE__, __LINE__, __FUNCTION__}, ""};
    fatdog::stdout_sink sink;
    sink.set_formatter(std::move(new_formatter));
    sink.log(event);
}

TEST_CASE("log", "[logger]")
{
    fatdog::logger log_msg("test");
    log_msg.set_formatter(fatdog::detail::make_unique<fatdog::formatter>("[%Y-%m-%d] [%n] [%l] %v"));
    log_msg.info("hello, logger!");
}

TEST_CASE("factory", "[synchronous_factory]")
{
    std::string logger_name = "test";
    auto new_logger = fatdog::synchronous_factory::create<fatdog::stdout_sink>(logger_name);
    new_logger->info("hello, factory!");
}

TEST_CASE("logger_format", "[logger]")
{
    std::string logger_name = "test";
    auto new_logger = fatdog::synchronous_factory::create<fatdog::stdout_sink>(logger_name);
    new_logger->info("\n┌{0:─^{2}}┐\n"
  "│{1: ^{2}}│\n"
  "└{0:─^{2}}┘\n", "", "Hello, world!", 20);
    new_logger->info(123456);
}