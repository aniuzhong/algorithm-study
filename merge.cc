#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <functional>

#include "algorithm_lite.h"

auto print = [](auto const rem, auto const& v) {
  std::cout << rem;
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << '\n';
};

int main() {
  // fill the vectors with random numbers
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dis(0, 100);

  std::vector<int> v1(10), v2(20);
  std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
  std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));

  print("Originally:\nv1: ", v1);
  print("v2: ", v2);

  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  print("After sorting:\nv1: ", v1);
  print("v2: ", v2);

  // merge
  std::vector<int> dst;
  Merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));

  print("After merging:\ndst: ", dst);
}