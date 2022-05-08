#include <bits/stdc++.h>

int removeDuplicates(std::vector<int>& nums) {
  auto it = std::unique(nums.begin(), nums.end());
  return static_cast<int>(std::distance(nums.begin(), it));
}

int main() {
  // 
}
