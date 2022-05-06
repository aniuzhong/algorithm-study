#include <iostream>
#include <vector>

#include "algorithm_lite.h"

int main(int argc, char const* argv[]) {
  std::vector<int> myvector{10, 20, 20, 20, 30, 30, 20, 20, 10};
  ForEach(myvector.begin(), myvector.end(),
          [](const auto& e) { std::cout << e << ' '; });
  std::cout << '\n';
  auto it = Unique(myvector.begin(), myvector.end());
  (void)it;
  ForEach(myvector.begin(), myvector.end(),
          [](const auto& e) { std::cout << e << ' '; });
  std::cout << '\n';
  
  return 0;
}
