#include <iostream>

#include "memory_lite.h"

struct S {
  int x;
  float y;
  double z;

  S(int x, float y, double z) : x{x}, y{y}, z{z} { std::cout << "S::S();\n"; }

  ~S() { std::cout << "S::~S();\n"; }

  void print() const {
    std::cout << "S { x=" << x << "; y=" << y << "; z=" << z << "; };\n";
  }
};

int main() {
  alignas(S) unsigned char storage[sizeof(S)];

  S* ptr = ConstructAt(reinterpret_cast<S*>(storage), 42, 2.71828f, 3.1415);
  ptr->print();

  DestroyAt(ptr);
}