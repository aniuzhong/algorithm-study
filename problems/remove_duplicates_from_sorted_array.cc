#include <bits/stdc++.h>

namespace detail {

template <typename ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last) {
  if (first == last) return last;
  auto result = first;
  while (++first != last) {
    if (*first != *result) {
      ++result;
      if (first != result) {
        *result = std::move(*first);
      }
    }
  }
  return ++result;  // logic 'end'
}

}  // namespace detail

int removeDuplicates(std::vector<int>& nums) {
  auto it = std::unique(nums.begin(), nums.end());
  return static_cast<int>(std::distance(nums.begin(), it));
}

int main() {
  // 1 2 1 3 4 5 3 4 5
  //                   ^
  //           ^
  std::string line;
  while (std::getline(std::cin, line)) {
    std::vector<int> nums;
    std::stringstream ss;
    ss.str(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
      nums.emplace_back(std::stoi(item));
    }
    int ret = removeDuplicates(nums);
    for (int i = 0; i < ret; ++i) {
      std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
  }
}
