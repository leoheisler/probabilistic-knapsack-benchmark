#include "AuxFunct.h"


void print_array(int n, int* vector) {

  std::cout << "[ ";
  for (int i = 0; i < n; ++i) {
    std::cout << vector[i] << " ";
  }
  std::cout << "]" << std::endl;
}

void print_matrix(int i, int j, int** matrix) {
  for (int row = 0; row < i; ++row) {
      for (int col = 0; col < j; ++col) {
          std::cout << matrix[row][col] << " ";
      }
      std::cout << std::endl;
  }
}

void permute_values(int n, int* values, int* weights){
  std::vector<std::pair<int, int>> items(n);
  for (int i = 0; i < n; ++i) {
      items[i] = {values[i], weights[i]};
  }

  std::random_device rd;
  std::default_random_engine rng(rd());
  std::shuffle(items.begin(), items.end(), rng);

  for (int i = 0; i < n; ++i) {
      values[i] = items[i].first;
      weights[i] = items[i].second;
  }
}