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
    } else {  // not less than (lower_bound)
      count = step;     
    }
  }
  return first;
}

template <typename ForwardIt, typename T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value) {
  ForwardIt it;
  typename std::iterator_traits<ForwardIt>::difference_type count, step;
  count = std::distance(first, last);
  while (count > 0) {
    it = first;
    step = count / 2;
    std::advance(it, step);
    if (*it <= value) {
      first = ++it;
      count -= step;
    } else { // greater than (upper_bound)
      count = step;
    }
  }
  return first;
}
}  // namespace detail

std::vector<int> searchRange(std::vector<int>& nums, int target) {
  auto left_iter = detail::lower_bound(nums.begin(), nums.end(), target);
  if (left_iter != nums.end() && *left_iter == target) {
    auto right_iter = detail::upper_bound(nums.begin(), nums.end(), target);
    return {static_cast<int>(std::distance(nums.begin(), left_iter)),
            static_cast<int>(std::distance(nums.begin(), right_iter) - 1)};
  } else {
    return {-1, -1};
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

    auto ret = searchRange(nums, target);

    std::cout << ret[0] <<',' << ret[1] << std::endl;
  }


}