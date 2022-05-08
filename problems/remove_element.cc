#include <bits/stdc++.h>

namespace detail {

template <typename ForwardIt, typename T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value) {
  first = std::find(first, last, value);
  if (first != last) {
    for (ForwardIt i = first; i != last; ++i) {
      if (*i != value) *first++ = std::move(*i);
    }
  }
  return first;
}

}  // namespace detail

int removeElement(std::vector<int>& nums, int val) { 
  auto it = detail::remove(nums.begin(), nums.end(), val);
  int index = static_cast<int>(std::distance(nums.begin(), it));
  return index; 
}

int main(int argc, char* argv[]) {
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
    int val = stoi(line);

    auto ret = removeElement(nums, val);

    std::cout << ret << std::endl;
  }

}
