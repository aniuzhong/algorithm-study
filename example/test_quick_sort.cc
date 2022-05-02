#include <array>
#include <forward_list>
#include <iostream>
#include <string_view>

#include "algorithm_lite.h"
int main() {
  std::forward_list<int> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

  auto print = [&s](std::string_view const rem) {
    for (auto a : s) {
      std::cout << a << ' ';
    }
    std::cout << ": " << rem << '\n';
  };

  QuickSort(s.begin(), s.end());
  print("sorted with the default operator<");
}