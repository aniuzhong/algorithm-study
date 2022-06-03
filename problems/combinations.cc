#include <iostream>
#include <vector>

int g_count = 0;

void PrintIndent(int n) {
  for (int i = 0; i < n; ++i) printf("                ");
}

std::vector<std::vector<int>> g_decision_paths;
std::vector<int> g_decision_path;

void helper(int n, int k, int start_index) {
  PrintIndent(g_count++);
  std::cout << "start_index:" << start_index << ", k" << k << std::endl;
  
  if (k == 0) {
    g_decision_paths.push_back(g_decision_path);
    PrintIndent(--g_count);
    std::cout << "return" << std::endl;
    return;
  }

  for (int i = start_index; i <= n; ++i) {
    g_decision_path.push_back(i);
    ++i;
    --k;
    helper(n, k, i);
    --i;
    ++k;
    g_decision_path.pop_back();
  }

  PrintIndent(--g_count);
  std::cout << "return" << std::endl;
}

std::vector<std::vector<int>> combine(int n, int k) {
  helper(n, k, 1);
  return g_decision_paths;
}

int main() {
  //
}