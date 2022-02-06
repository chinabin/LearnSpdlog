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