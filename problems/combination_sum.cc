#include <iostream>
#include <vector>

int g_count;

void PrintIndent(int n) {
  for (; n > 0; --n) printf("            ");
}

std::vector<int> g_decision_path;
std::vector<std::vector<int>> g_decision_paths;

void helper(std::vector<int>& candidates, size_t n, int target, int sum) {
  PrintIndent(g_count++);
  std::cout << "["
            << "candidates:" << candidates[n] << ",sum:" << sum
            << ",target:" << target << "]" << std::endl;

  if (sum == target) {
    PrintIndent(--g_count);
    std::cout << "return" << std::endl;
    g_decision_paths.push_back(g_decision_path);
    return;
  }

  for (size_t i = n; i < candidates.size() && candidates[i] <= target - sum; ++i) {
    g_decision_path.push_back(candidates[i]);
    sum += candidates[i];
    helper(candidates, i, target, sum);
    sum -= candidates[i];
    g_decision_path.pop_back();
  }
  PrintIndent(--g_count);
  std::cout << "return" << std::endl;
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates,
                                             int target) {
  helper(candidates, 0, target, 0);
  return g_decision_paths;
}

int main() {
  //
}
