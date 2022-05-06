#include <iostream>
#include <vector>

#include "algorithm_lite.h"

int main(int argc, char const* argv[]) {
  std::vector<int> myvector{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ForEach(myvector.begin(), myvector.end(),
          [](const auto& e) { std::cout << e << ' '; });
  std::cout << '\n';
  auto it = Partition(myvector.begin(), myvector.end(),
                      [](const auto& e) { return e % 2; });
  (void)it;
  ForEach(myvector.begin(), myvector.end(),
          [](const auto& e) { std::cout << e << ' '; });
  std::cout << '\n';

  return 0;
}