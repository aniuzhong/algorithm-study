#include <array>
#include <forward_list>
#include <iostream>
#include <string_view>

#include "algorithm_lite.h"
int main() {
  std::vector<int> s{8, 3, 5, 4, 0, 2, 4, 9, 6, 1};

  auto print = [&s](std::string_view const rem) {
    for (auto a : s) {
      std::cout << a << ' ';
    }
    std::cout << ": " << rem << '\n';
  };

  QuickSort(s.begin(), s.end());
  print("sorted with the default operator<");
}