# LearnSpdlog

## 安装事项
* 记得使用 bash ，而不是 fish 。
* 安装 benchmark

    * 如果 gcc 是 4.8 ，记得升级
    ```bash
    $ git clone https://github.com/google/benchmark.git
    $ cd benchmark
    $ cmake -E make_directory "build"
    $ cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../
    $ sudo cmake --build "build" --config Release --target install
    ```
* 编译 spdlog: `cmake3 -DSPDLOG_BUILD_ALL=ON ..`


-----


## 模块
- sink 负责日志落地
    ```c++
    /*
     * 包含 formatter 和 level ，通过 level 判断是否输出日志，通过
     * formatter 格式化日志并落地。
     * 写日志的时候如果发现 formatter 为空，则创建一个默认的。
    */
    // 1. 调用 formatter 的 format 接口将日志格式化并落地
    virtual void log(const log_event& msg) = 0;
    // 2. 设置 formatter 
    virtual void set_formatter(std::unique_ptr<formatter>&& fmter) = 0;
    virtual void set_pattern(const std::string&) = 0;
    // 3. 立即刷新日志缓存
    virtual void flush_now() = 0;
    // 4. 日志等级控制
    bool should_log(LOG_LEVEL level);
    LOG_LEVEL get_level();
    void set_level(LOG_LEVEL level);
    ```
- formatter 负责格式化日志
    ```c++
    // 1. 传递格式字符串初始化 formatter ，调用 parse 解析传入的格式
    formatter(const std::string& pattern);
    // 2. 传入日志原始数据，传出格式化之后的日志数据
    std::string format(const log_event& msg);
    // 3. 克隆自己，属于 helper 函数
    std::unique_ptr<formatter> clone();
    // 4. 解析格式字符串，变成一个个 format_item
    void parse();
    ```
- log_event 负责产生日志
    ```c++
    /*
     * 携带日志信息，包括日志内容、等级、所在文件名、所在文件行、所在行数名、日志时间、线程id 。
     * 这些携带的信息会被 formatter 使用，用来产生格式化的数据。
    */
    ```
- logger 负责管理 sink
    ```c++
    /*
     * logger 包含了多个 sink ，接收日志，然后落地。
    */
    // 1. logger 拥有名字，但是没有 formatter , formatter 是和 sink 绑定的。
    logger(const std::string& logger_name);
    logger(const std::string& logger_name, std::unique_ptr<sink> s);
    // 2. 将新的 formatter 通过 clone 传给 sink 
    void set_formatter(std::unique_ptr<formatter> formatter);
    // 3. 设置 logger 的 level 。日志传递进来首先会被 logger 的 level 进行判断，然后会被 sink 的 level 判断
    void set_level(LOG_LEVEL level);
    LOG_LEVEL get_level() const;
    std::string name();
    void add_sink(std::unique_ptr<sink> s);
    // 4. 打印日志
    // 形式一: info(123); info("lalala")
    // 形式二: info("{1} {0}", "world", "hello");
    ```
- registry 负责管理 logger
    ```c++
    /*
     * registry 相当于 logger 的中心管理，会将所有的调用转换到 logger 层面。
     * registry 有默认的 default_logger ，全局的 formatter level ，当新的 logger 
     * 注册进来的时候用来设置配置。
    */
    // 1. registry 的实例化对象接口
    static registry &instance();
    // 2. 通过名字注册 logger ，使得此 logger 能被 registry 管理
    void register_logger(std::shared_ptr<logger> new_logger);
    // 3. 初始化 logger ，主要是设置 formatter level ，并且注册此 logger
    void initialize_logger(std::shared_ptr<logger> new_logger);
    // 4. 获取 logger 或者 default_logger
    std::shared_ptr<logger> get(const std::string &logger_name);
    std::shared_ptr<logger> default_logger();
    logger* default_logger_raw() { return _default_logger.get(); }
    // 5. 设置配置，将新参数传递给各个 logger 和更新全局配置。
    void set_formatter(std::unique_ptr<formatter> fmter);
    void set_level(LOG_LEVEL lvl);
    void set_automatic_registration(bool v) { _automatic_registration = v; }
    void set_default_logger(std::shared_ptr<logger> new_logger);
    // 6. 从 registry 中去除对应 logger 的管理
    void drop(const std::string& logger_name);
    void drop_all();
    ```