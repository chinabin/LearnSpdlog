git clone https://github.com/fmtlib/fmt

CMakeLists.txt 加上
add_subdirectory(dependencies/fmt EXCLUDE_FROM_ALL)
target_link_libraries(fmt_demo fmt-header-only)

```c++
// 基础用法
fmt::print("Hello, {}!", "world");
fmt::print("Hello, {0}, {0}", "world");

// 格式化
fmt::memory_buffer buf;
fmt::format_to(buf, "{}", 42);
fmt::format_to(buf, "{:x}", 42); // 十六进制表示
std::cout << buf.data();

std::time_t t = std::time(nullptr);
fmt::print("The date is {:%Y-%m-%d}.\n", *std::localtime(&t));

// 保留两位小数
std::string s = fmt::format("The answer is {:.2f}", 1.12345678);

// 别名参数
fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.",
           fmt::arg("name", "World"), fmt::arg("number", 42));

std::vector<int> v = {1, 2, 3};
fmt::print("{}\n", v);

// 输出到文件
auto out = fmt::output_file("guide.txt");
out.print("Don't {}", "Panic");

// 颜色
fmt::print(fmt::color::red, "hello {}\n", "world");
fmt::print(fmt::rgb(10, 50, 63), "hello {}\n", "world");
```