#include <iostream>

bool isPowerOfFour(int num) {
  //check(is or not) a power of 2.
  if (num < 0 || num & (num-1)){
      return false;
  }
  //check 1 on odd bits
  return num & 0x55555555;
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int num = stoi(line);
    auto ret = isPowerOfFour(num);
    std::cout << ret << std::endl;
  }
  return 0;
}