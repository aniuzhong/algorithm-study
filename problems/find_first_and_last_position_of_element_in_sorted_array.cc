#include <bits/stdc++.h>

std::vector<int> searchRange(std::vector<int>& nums, int target) {
  auto left_iter = std::lower_bound(nums.begin(), nums.end(), target);
  if (left_iter != nums.end() && *left_iter == target) {
    auto right_iter = std::upper_bound(nums.begin(), nums.end(), target);
    return {static_cast<int>(std::distance(nums.begin(), left_iter)),
            static_cast<int>(std::distance(nums.begin(), right_iter) - 1)};
  } else {
    return {-1, -1};
  }
}

int main() {
  //
}