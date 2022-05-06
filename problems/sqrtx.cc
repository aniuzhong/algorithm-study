#include <bits/stdc++.h>

int mySqrt(int x) {
  if (x == 0 || x == 1) return x;

  size_t first = 0, last = static_cast<size_t>(x) + 1;
  size_t value = static_cast<size_t>(x);
  size_t count = last - first;
  size_t it, step;

  while (count > 0) {
    it = first;
    step = count / 2;
    it += step;
    if (it * it < value) { // 
      first = ++it;
      count -= step + 1;
    } else {
      count = step;
    }
  }

  // make gcc happy
  if (first != last && first * first == value) {
    int* ptr = static_cast<int*>(static_cast<void*>(&first));
    return *ptr;
  } else {
    int* ptr = static_cast<int*>(static_cast<void*>(&(--first)));
    return *ptr;
  }
}

int main() {
  //
}