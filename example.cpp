#include "logger.h"
#include "common_func.h"
#include "synchronous_factory.h"
#include "stdout_sinks.h"


int main()
{
    std::string logger_name = "test";
    auto new_logger = fatdog::synchronous_factory::create<fatdog::stdout_sink>(logger_name);
    new_logger->info("\n┌{0:─^{2}}┐\n"
                    "│{1: ^{2}}│\n"
                    "└{0:─^{2}}┘\n", "", "Hello, world!", 20);
    new_logger->info(123456);

    return 0;
}