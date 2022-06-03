#include <atomic>
#include <thread>
#include <iostream>
#include <benchmark/benchmark.h>

void update(std::atomic<int>& a) {
  for (int i = 0; i < 3000000; ++i) {
    ++a;
  }
}

struct alignas(64) padded_atomic_int {
  padded_atomic_int() { value = 0; }
  std::atomic<int> value;
};

void multi_thread_padding() {
  padded_atomic_int a{};
  padded_atomic_int b{};

  std::thread t1([&]() { update(a.value); });
  std::thread t2([&]() { update(b.value); });

  t1.join();
  t2.join();
}

void single_thread() {
  std::atomic<int> a, b;
  a = b = 0;

  update(a);
  update(b);
}

void false_sharing() {
  std::atomic<int> a, b;
  a = b = 0;

  std::thread t1([&]() { update(a); });
  std::thread t2([&]() { update(b); });

  t1.join();
  t2.join();
}

void print() {
  std::atomic<int> a, b;
  
  std::cout << "&a:" << &a << std::endl;
  std::cout << "&b:" << &b << std::endl;
}

static void single_thread_benchmark(benchmark::State& s) {
  while (s.KeepRunning()) single_thread();
}

BENCHMARK(single_thread_benchmark);

static void multi_thread_padding_benchmark(benchmark::State& s) {
  while (s.KeepRunning()) multi_thread_padding();
}

BENCHMARK(multi_thread_padding_benchmark);

static void false_sharing_benchmark(benchmark::State& s) {
  while (s.KeepRunning()) false_sharing();
}

BENCHMARK(false_sharing_benchmark);

BENCHMARK_MAIN();