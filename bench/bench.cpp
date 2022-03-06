#include <benchmark/benchmark.h>

#include "logger.h"
#include "common_func.h"
#include "synchronous_factory.h"
#include "stdout_sinks.h"


static void bench_test(benchmark::State& state)
{
    std::string logger_name = "test";
    auto new_logger = fatdog::synchronous_factory::create<fatdog::stdout_sink>(logger_name);
    for (auto _: state) {
        new_logger->info("hello, factory!\n");
    }
}
BENCHMARK(bench_test);


BENCHMARK_MAIN();