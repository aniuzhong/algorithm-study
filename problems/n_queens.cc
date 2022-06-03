#include <iostream>
#include <vector>

int g_count;

void PrintIndent(int n) {
  for (int i = n; n > 0; --n) printf("            ");
}

std::vector<std::string> g_decision_path;
std::vector<std::vector<std::string>> g_decision_paths;


void helper(int n, int row, std::vector<std::string> chessboard) {
  if (row > n) {
    g_decision_paths.push_back(g_decision_path);
    return;
  }

  std::string decisions = chessboard[row];

  chessboard[row - 1];
  for (int i = 0; i < n; ++i) {
    if (chessboard[row - 1][i] = 'Q') {
      decisions[i] = 'Q';
    }
  }

  for (const auto& decision : decisions) {
    if (decision != 'Q') {
      // g_decision_path.push_back(decision);
    }
  }
}

std::vector<std::vector<std::string>> solveNQueens(int n) {
  std::vector<std::string> chessboard;
  for (int i = 0; i < 4; ++i) chessboard.push_back(std::string(n, '.'));
  // helper(n);
  return g_decision_paths;
}