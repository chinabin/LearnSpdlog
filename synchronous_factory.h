#include <memory>

#include "sinks/sink.h"
#include "logger.h"
#include "common_func.h"


namespace fatdog {

struct synchronous_factory {
    template<typename Sink, typename... SinkArgs>
    static std::shared_ptr<logger> create(std::string name, SinkArgs&&... args) {
        auto sink = detail::make_unique<Sink>(std::forward<SinkArgs>(args)...);
        auto new_logger = std::make_shared<logger>(name, std::move(sink));

        return new_logger;
    }
};

}