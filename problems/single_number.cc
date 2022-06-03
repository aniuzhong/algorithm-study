#include <iostream>
#include <sstream>
#include <vector>

int singleNumber(std::vector<int>& nums) {
  int ans = 0;
  for (const auto& num : nums) ans ^= num;
  return ans;
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
    auto ret = singleNumber(nums);
    std::cout << ret << std::endl;
  }
}