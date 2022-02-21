#include <memory>

#include "sinks/sink.h"
#include "logger.h"
#include "common_func.h"


namespace fatdog {

struct synchronous_factory {
    template<typename Sink>
    static std::shared_ptr<logger> create(std::string name) {
        auto sink = detail::make_unique<Sink>();
        auto new_logger = std::make_shared<logger>(name, std::move(sink));

        return new_logger;
    }
};

}