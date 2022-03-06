```c++
// 1. 使用 BENCHMARK、BENCHMARK_MAIN 宏
#include <benchmark/benchmark.h>

void BM_DemoSleep(benchmark::State& state) {
  for (auto _ : state){
    //待测试的代码
  }
}
BENCHMARK(BM_DemoSleep); 

BENCHMARK_MAIN(); 
```

```c++
// 2. 使用 Benchmark 接口
#include <benchmark/benchmark.h>
#include <chrono>
#include <thread>

void BM_DemoSleep(benchmark::State& state) {
  for (auto _ : state){
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000)); //待测试的代码
  }
}

void BM_DemoSleep1(benchmark::State& state, int id) {
  std::cout << "id:"<< id << std::endl;
  for (auto _ : state){
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
  }
}

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv); // 初始化Benchmark
  if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
  
  // 使用函数指针注册
  ::benchmark::RegisterBenchmark("BM_DemoSleep", &BM_DemoSleep);
  // 使用 Lamba 函数注册
  ::benchmark::RegisterBenchmark("BM_DemoSleep1", [](benchmark::State& state){
    for (auto _ : state){
      std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    }
  });
  
  // 使用带参数的函数指针注册
  int id = 10;
  ::benchmark::RegisterBenchmark("BM_DemoSleep2", &BM_DemoSleep1, id);
  
  ::benchmark::RunSpecifiedBenchmarks(); // 运行
  ::benchmark::Shutdown(); 
}
```