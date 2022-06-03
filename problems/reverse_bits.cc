#include <iostream>

uint32_t reverseBits(uint32_t n) {
  uint32_t ans = 0;
  for (int i = 0; i < 32; i++) {
    ans <<= 1;
    ans |= n & 0x00000001;
    n >>= 1;
  }
  return ans;
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    uint32_t n = stoi(line);
    uint32_t ret = reverseBits(n);
    std::string out = std::to_string(ret);
    std::cout << out << std::endl;
  }
  return 0;
}