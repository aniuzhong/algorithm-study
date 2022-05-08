#include <bits/stdc++.h>

namespace detail {

template <typename ForwardIt, typename T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value) {
  ForwardIt it;
  auto count = std::distance(first, last);
  decltype(count) step;
  while (count > 0) {
    it = first;
    step = count / 2;
    std::advance(it, step);
    if (*it < value) {
      first = ++it;
      count -= step + 1;
    } else {
      count = step;
    }
  }
  return first;
}

}  // namespace detail

int searchInsert(std::vector<int>& nums, int target) {
  auto it = detail::lower_bound(nums.begin(), nums.end(), target);
  return static_cast<int>(std::distance(nums.begin(), it));
}

int main() {
  // std::vector<int> v{1,2,2,2,3,4,5,5,6};
  // std::for_each(v.begin(), v.end(), [](const auto& e) {std::cout << e << " ";});
  // std::cout << std::endl;

  // auto it = detail::lower_bound(v.begin(), v.end(), 2);
  // std::cout << "it:" << std::distance(v.begin(), it)
  //           << " ,*it:" << *it << std::endl;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::vector<int> nums;
    std::stringstream ss;
    ss.str(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
      nums.emplace_back(stoi(item));
    }

    std::getline(std::cin, line);
    int target = stoi(line);

    auto ret = searchInsert(nums, target);

    std::cout << ret << std::endl;
  }
  
   
}