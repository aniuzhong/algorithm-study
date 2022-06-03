#include <bits/stdc++.h>

bool isPerfectSquare(int num) {
  size_t first, last, value, it, count, step;
  first = 0;
  last = static_cast<size_t>(num) + 1;
  value = num;
  count = first - last;

  while (count > 0) {
    it = first;
    step = count / 2;
    it += step;
    if (it * it < value) {
      first = ++it;
      count -= step + 1;
    } else { // 'it*it' not less than 'value'
      count = step;
    }
  }

  if (first != last && first * first == value) {
    return true;
  } else {
    return false;
  }
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    int num = std::stoi(line);
    bool ret = isPerfectSquare(num);
    std::cout << std::boolalpha << ret << std::endl;
  }
}