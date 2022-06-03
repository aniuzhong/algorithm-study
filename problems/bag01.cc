#include <iostream>
#include <unordered_map>
#include <vector>

class Stone {
 public:
  Stone(int32_t weight, int32_t value) : weight_(weight), value_(value) {}
  int32_t weight() const { return weight_; }
  int32_t value() const { return value_; }

 private:
  int32_t weight_;
  int32_t value_;
};

int g_count;

void PrintIndent(int n) {
  for (; n > 0; --n) printf("                 ");
}

std::vector<int32_t> g_decision_path;
int32_t g_value;
std::vector<std::vector<int32_t>> g_decision_paths;
std::vector<int32_t> g_values;
std::unordered_map<int32_t, int32_t> g_memo;

void helper(std::vector<Stone>& stones, int32_t weight, size_t start_index) {
  PrintIndent(g_count++);
  std::cout << "weight:" << weight << ", start_index:" << start_index;

  if (g_memo.find(weight) != g_memo.end()) {
    std::cout << "memo.";
  }

  std::cout << std::endl;
  
  if (weight == 0) {
    g_decision_paths.push_back(g_decision_path);
    g_values.push_back(g_value);
    PrintIndent(--g_count);
    printf("return\n");
    return;
  }

  if (weight < 0) {
    PrintIndent(--g_count);
    printf("return\n");
    return;
  }

  for (size_t i = start_index; i < stones.size(); ++i) {
    g_decision_path.push_back(stones[i].weight());
    ++start_index;
    weight -= stones[i].weight();
    g_value += stones[i].value();
    helper(stones, weight, start_index);
    g_memo[weight] = g_value;  // ?
    g_decision_path.pop_back();
    --start_index;
    weight += stones[i].weight();
    g_value -= stones[i].value();
  }

  PrintIndent(--g_count);
  printf("return\n");
  return;
}

std::vector<std::vector<int32_t>> CombinationSum(std::vector<Stone>& stones,
                                                 int32_t weight) {
  helper(stones, weight, 0);
  return g_decision_paths;
}

int main() {
  std::vector<Stone> stones;
  stones.emplace_back(2, 6);
  stones.emplace_back(2, 3);
  stones.emplace_back(6, 5);
  stones.emplace_back(5, 4);
  stones.emplace_back(4, 6);

  int32_t max_weight = 8;

  auto ret = CombinationSum(stones, max_weight);

  std::cout << "Weight:" << std::endl;
  for (const auto& vec_int : ret) {
    std::cout << "[ ";
    for (const auto& i : vec_int) std::cout << i << ' ';
    std::cout << "]" << std::endl;
  }

  std::cout << "Value:" << std::endl;
  for (const auto& v : g_values) {
    std::cout << v << std::endl;
  }
}
