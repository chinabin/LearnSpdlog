#include "includes.h"

#include "stdout_sinks.h"

TEST_CASE("a demo", "[demo]")
{
    std::cout << "hello, fatdog~" << std::endl;
    REQUIRE(1 == 1);
}

TEST_CASE("stdout_sink", "[stdout_sink]")
{
    fatdog::sinks::stdout_sink sink;
    sink.log("hello, stdout_sink\n");
}