#include <algorithm>
#include <iostream>
#include <vector>

int maxProduct(std::vector<std::string>& words) {
  std::vector<int> products(1, 0);
  for (size_t i = 0; i < words.size(); ++i) {
    for (size_t j = i + 1; j < words.size(); ++j) {
      for (const auto& s_i : words[i]) {
        for (const auto& s_j : words[j]) {
          if (s_i == s_j) goto end_for_j;
        }
      }
      std::cout << "i:" << words[i] << ",j:" << words[j] << std::endl;
      std::cout << "i:" << words[i].size() << ",j:" << words[j].size()
                << std::endl;
      std::cout << "p:" << words[i].size() * words[j].size() << std::endl;
      products.push_back(static_cast<int>(words[i].size() * words[j].size()));
    end_for_j:;
    }
  }
  return *std::max_element(products.begin(), products.end());
}

int main() {
  //
}