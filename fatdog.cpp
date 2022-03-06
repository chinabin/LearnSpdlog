#include "fatdog.h"

namespace fatdog {

void initialize_logger(std::shared_ptr<logger> new_logger)
{
    registry::instance().initialize_logger(new_logger);
}

std::shared_ptr<logger> get(const std::string& logger_name)
{
    return registry::instance().get(logger_name);
}

void set_formatter(std::unique_ptr<formatter> fmter)
{
    registry::instance().set_formatter(std::move(fmter));
}

void set_pattern(const std::string& pattern)
{
    set_formatter(detail::make_unique<formatter>(pattern));
}

void set_level(LOG_LEVEL lvl)
{
    registry::instance().set_level(lvl);
}

void register_logger(std::shared_ptr<logger> new_logger)
{
    registry::instance().register_logger(new_logger);
}

void drop(const std::string& logger_name)
{
    registry::instance().drop(logger_name);
}

void drop_all()
{
    registry::instance().drop_all();
}

void set_automatic_registration(bool v)
{
    registry::instance().set_automatic_registration(v);
}

std::shared_ptr<logger> default_logger()
{
    return registry::instance().default_logger();
}

logger* default_logger_raw()
{
    return registry::instance().default_logger_raw();
}

void set_default_logger(std::unique_ptr<logger> lgger)
{
    registry::instance().set_default_logger(std::move(lgger));
}

void log()
{}

}