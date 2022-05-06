#include <bits/stdc++.h>

namespace detail {

template <typename ForwardIt, typename T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value) {
  ForwardIt it;
  typename std::iterator_traits<ForwardIt>::difference_type count, step;
  count = std::distance(first, last);
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

int search(std::vector<int>& nums, int target) {
  auto it = detail::lower_bound(nums.begin(), nums.end(), target);
  if (it != nums.end() && *it == target) {
    return static_cast<int>(std::distance(nums.begin(), it));
  } else {
    return -1;
  }
}

int main() {
  std::string line;

  while (std::getline(std::cin, line)) {
    std::vector<int> nums;
    std::stringstream ss;
    ss.str(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
      nums.push_back(stoi(item));
    }

    std::getline(std::cin, line);
    int target = stoi(line);

    int ret = search(nums, target);

    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }

  return 0;
}
