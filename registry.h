#include <unordered_map>
#include <string>
#include <memory>

#include "logger.h"

namespace fatdog {

class registry {
public:
    // std::shared_ptr<registry> instance();
    static registry &instance();

    void register_logger(std::shared_ptr<logger> new_logger);
    void initialize_logger(std::shared_ptr<logger> new_logger);
    std::shared_ptr<logger> get(const std::string &logger_name);
    std::shared_ptr<logger> default_logger();
    void set_formatter(std::unique_ptr<formatter> fmter);
    void set_level(LOG_LEVEL lvl);
    void set_automatic_registration(bool v) { _automatic_registration = v; }
    logger* default_logger_raw() { return _default_logger.get(); }
    void set_default_logger(std::shared_ptr<logger> new_logger);
    void drop(const std::string& logger_name);
    void drop_all();

private:
    registry();
    ~registry();

    std::unordered_map<std::string, std::shared_ptr<logger>> _logger_map;
    std::shared_ptr<logger> _default_logger;
    LOG_LEVEL _level{ LOG_LEVEL::LOG_LEVEL_INFO };
    std::unique_ptr<formatter> _formatter;
    bool _automatic_registration{false};
};

}