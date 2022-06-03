#include <iostream>
#include <unordered_map>
#include <vector>

int g_count;

void PrintIndent(int n) {
  for (; n > 0; --n) printf("            ");
}

std::unordered_map<char, std::string> g_table{
    {'0', " "},   {'1', "*"},   {'2', "abc"},  {'3', "def"}, {'4', "ghi"},
    {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

std::string g_decision_path;
std::vector<std::string> g_decision_paths;

void helper(const std::string& digits, size_t n) {
  PrintIndent(g_count++);
  std::cout << "[" << n << "," << digits[n] << "]" << std::endl;

  if (n == digits.size()) {
    PrintIndent(--g_count);
    std::cout << "return" << std::endl;
    g_decision_paths.push_back(g_decision_path);
    return;
  }

  std::string decisions = g_table[digits[n]];
  for (const auto& decision : decisions) {
    g_decision_path.push_back(decision);
    ++n;
    helper(digits, n);
    --n;
    g_decision_path.pop_back();
  }
  PrintIndent(--g_count);
  std::cout << "return" << std::endl;
}

std::vector<std::string> letterCombinations(std::string digits) {
  helper(digits, 0);
  return g_decision_paths;
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string digits = line;
    std::vector<std::string> ret = letterCombinations(digits);

    std::cout << '[' << std::endl;
    for (const auto& str : ret) {
      std::cout << "\t\"" << str << "\"" << std::endl;
    }
    std::cout << ']' << std::endl;

    g_decision_paths.clear();
  }
}
