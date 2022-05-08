#include <bits/stdc++.h>

// auto print = [](auto const& remark, auto const& first, auto const& last) {
//     std::cout << remark;
//     for (auto i = first; i != last; ++i)
//         std::cout << *i << ' ';
//     std::cout << '\n';
// };

// template <typename ForwardIt, typename T>
// ForwardIt __search(ForwardIt first, ForwardIt last, const T& value) {
//     if (first == last) return first;

//     ForwardIt it;
//     size_t count = std::distance(first, last);
//     size_t step = count / 2;
//     it = first;
//     // 5 6 7 0 1 2 3 4 
//     //         ^
//     std::advance(it, step);
//     if (*it < *first) {
//         print("@", std::next(it, 1), last);
//         auto it1 = std::lower_bound(std::next(it, 1), last, value);
//         // 5 6 7 0
//         __search(first, it, value);
//     } else {
//         auto it2 = std::lower_bound(first, it, value);
//         std::cout << "@" << std::endl;
//         __search(first, it, value);
//     }

//     return first;
// }

// class Solution {
// public:
//     int search(std::vector<int>& nums, int target) {
//         __search(nums.begin(), nums.end(), target);
//         return 0;
//     }
// };

int main() {
  //
}