1. 对于 `sinks`，以 `_mt` 后缀结尾的是线程安全的，比如：`daily_file_sink_mt`   
   以 `_st` 后缀结尾的是非线程安全的，比如：`daily_file_sink_st`

2. Each logger contains a vector of one or more std::shared_ptr<spdlog::sink>.

    On each log call (if the log level is right) the logger will call the sink(log_msg) function on each of them.

    Sinks are the objects that actually write the log to their target. Each sink should be responsible for only single target (e.g file, console, db), and each sink has its own private instance of formatter object.

3. 创建 `logger` 的方法:
```c++
    auto console = spdlog::stdout_color_mt("some_unique_name");

    spdlog::get("logger_name");

    // 手动创建 logger 并注册
    auto my_logger= std::make_shared<spdlog::logger>("mylogger", sink);
    spdlog::register_logger(my_logger);
```

```c++
// Create and register a logger with a templated sink type
// The logger's level, formatter and flush level will be set according the
// global settings.
//
// Example:
//   spdlog::create<daily_file_sink_st>("logger_name", "dailylog_filename", 11, 59);
template <typename Sink, typename... SinkArgs>
std::shared_ptr< spdlog::logger > create(std::string logger_name, SinkArgs &&...sink_args)



// Initialize and register a logger,
// formatter and flush level will be set according the global settings.
//
// Useful for initializing manually created loggers with the global settings.
//
// Example:
//   auto mylogger = std::make_shared<spdlog::logger>("mylogger", ...);
//   spdlog::initialize_logger(mylogger);
SPDLOG_API void initialize_logger(std::shared_ptr<logger> logger);



// Return an existing logger or nullptr if a logger with such name doesn't exist.
// example: spdlog::get("my_logger")->info("hello {}", "world");
SPDLOG_API std::shared_ptr<logger> get(const std::string &name);
```