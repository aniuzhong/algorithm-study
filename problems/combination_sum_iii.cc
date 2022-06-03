#include <iostream>
#include <vector>

int g_count;

void PrintIndent(int n) {
  for (; n > 0; --n) printf("               ");
}

std::vector<std::vector<int>> g_decision_paths;
std::vector<int> g_decision_path;

void helper(int k, int n, int start_index) {
  PrintIndent(g_count++);
  std::cout << "k:" << k << ",n:" << n << std::endl;
  if (k == 0) {
    if (n == 0) {
      g_decision_paths.push_back(g_decision_path);
    }
    PrintIndent(--g_count);
    std::cout << "return" << std::endl;
    return;
  }

  for (int i = start_index; i <= 9; ++i) {
    g_decision_path.push_back(i);
    n -= i;
    --k;
    ++i;
    helper(k, n, i);
    --i;
    ++k;
    n += i;
    g_decision_path.pop_back();
  }
  PrintIndent(--g_count);
  std::cout << "return" << std::endl;
}

std::vector<std::vector<int>> combinationSum3(int k, int n) {
  helper(k, n, 1);
  return g_decision_paths;
}

int main() {
  //
}