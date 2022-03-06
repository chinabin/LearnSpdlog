#include "logger.h"
#include "common_func.h"
#include "synchronous_factory.h"
#include "stdout_sinks.h"


int main()
{
    {
        std::string logger_name = "test";
        auto new_formatter = fatdog::detail::make_unique<fatdog::formatter>("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] (%s:%! - %#) %v");
        fatdog::log_event event{"hello, main\n", fatdog::LOG_LEVEL::LOG_LEVEL_INFO, {__FILE__, __LINE__, __FUNCTION__}, ""};
        fatdog::stdout_sink sink;
        sink.set_formatter(std::move(new_formatter));
        sink.log(event);
    }

    {
        std::string logger_name = "color~";
        auto new_logger = fatdog::synchronous_factory::create<fatdog::stdout_sink>(logger_name);
        auto new_formatter = fatdog::detail::make_unique<fatdog::formatter>("%^[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v%$");
        new_logger->set_formatter(std::move(new_formatter));
        new_logger->info("\n┌{0:─^{2}}┐\n"
                        "│{1: ^{2}}│\n"
                        "└{0:─^{2}}┘\n", "", "Hello, world!", 20);
        new_logger->trace(11111);
        new_logger->debug(22222);
        new_logger->info(33333);
        new_logger->warn(44444);
        new_logger->error(55555);
        new_logger->critical(66666);
    }

    return 0;
}