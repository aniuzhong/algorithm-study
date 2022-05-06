#include <bits/stdc++.h>

int searchInsert(std::vector<int>& nums, int target) {
  auto it = std::lower_bound(nums.begin(), nums.end(), target);
  return static_cast<int>(std::distance(nums.begin(), it));
}

int main() {
  //
}