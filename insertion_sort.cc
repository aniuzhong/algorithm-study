#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#include "algorithm_lite.h"

auto print = [](auto const rem, auto const& v) {
  std::cout << rem;
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << '\n';
};

int main(int argc, char const *argv[]) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dis(0, 100);

  std::vector<int> v1(10);
  std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
  print("Originally:\nv1: ", v1);

  InsertionSort(v1.begin(), v1.end());
  print("After sorting:\nv1: ", v1);

  return 0;
}