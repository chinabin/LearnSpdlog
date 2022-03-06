#include "registry.h"
#include "sinks/stdout_sinks.h"
#include "common_func.h"

namespace fatdog
{

registry::registry()
    :_formatter(new formatter("%+"))
{
    std::string default_logger_name = "";
    auto sink = detail::make_unique<stdout_sink>();
    _default_logger = std::make_shared<logger>(default_logger_name, std::move(sink));
    _logger_map[default_logger_name] = _default_logger;
}

registry::~registry()
{}
/*
 * 因为 make_shared 需要调用构造函数创建对象以及析构函数销毁对象，当它们俩是 private 的时候，肯定就不行。
 * 
 * class SomeClass {
    public:
        static std::shared_ptr<SomeClass> getInstance();
    
    private:
        SomeClass();
    };
    std::shared_ptr<SomeClass> SomeClass::getInstance()
    {
        struct MkShrdEnablr : public SomeClass {};
        auto instance = std::make_shared<MkShrdEnablr>();       // 包装一层
        
        return instance;
    }
*/
// std::shared_ptr<registry> registry::instance()
// {
//     if (!_registry_ptr) {
//         _registry_ptr = std::make_shared<registry>();
//     }
//     return _registry_ptr;
// }

registry &registry::instance()
{
    static registry s_instance;
    return s_instance;
}

void registry::register_logger(std::shared_ptr<logger> new_logger)
{
    if (_logger_map.find(new_logger->name()) == _logger_map.end()) {
        _logger_map[new_logger->name()] = std::move(new_logger);
    }
}

void registry::initialize_logger(std::shared_ptr<logger> new_logger)
{
    new_logger->set_formatter(_formatter->clone());
    new_logger->set_level(_level);
    if (_logger_map.find(new_logger->name()) == _logger_map.end()) {
        _logger_map[new_logger->name()] = new_logger;
    }
    else {
        throw("logger exists!");
    }
}

std::shared_ptr<logger> registry::get(const std::string &logger_name)
{
    auto it = _logger_map.find(logger_name);
    return (it != _logger_map.end() ? it->second : nullptr);
}

void registry::set_formatter(std::unique_ptr<formatter> fmter)
{
    _formatter = std::move(fmter);
    for (auto &it : _logger_map) {
        it.second->set_formatter(_formatter->clone());
    }
}

void registry::set_level(LOG_LEVEL lvl)
{
    _level = lvl;
    for(auto &it : _logger_map) {
        it.second->set_level(lvl);
    }
}

std::shared_ptr<logger> registry::default_logger()
{
    return _default_logger;
}

void registry::set_default_logger(std::shared_ptr<logger> new_logger)
{
    _logger_map.erase(_default_logger->name());

    _logger_map[new_logger->name()] = new_logger;
    _default_logger = new_logger;
}

void registry::drop(const std::string& logger_name)
{
    _logger_map.erase(logger_name);
    if (_default_logger && _default_logger->name() == logger_name) {
        _default_logger.reset();
    }
}

void registry::drop_all()
{
    _logger_map.clear();
    _default_logger.reset();
}



} // namespace fatdog
