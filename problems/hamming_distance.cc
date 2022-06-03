#include <iostream>

// int hammingDistance(int x, int y) {
//   int diff = x ^ y, ans = 0;
//   while (diff) {
//     ans += diff & 1;
//     diff >>= 1;
//   }
//   return ans;
// }

int hammingDistance(int x, int y) {
  uint32_t diff = x ^ y;
  int ans = 0;
  for (uint32_t i = 0x00000001; i != 0x80000000; i <<= 1) {
    if((diff & i) == i) {
      ++ans;
    };
  }
  return ans;
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int x = stoi(line);
    std::getline(std::cin, line);
    int y = stoi(line);

    int ret = hammingDistance(x, y);

    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }
  return 0;
}