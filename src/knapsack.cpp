
#include "Read.h" 
#include "AuxFunct.h"
#include <cmath>
#include <chrono> 
#include <vector>
#include <algorithm>
#include <climits>

int probabilistic_knapsack(int n, int W, int maxW, int* weights, int* values) {
  std::vector<std::vector<int>> knapsack_matrix(n + 1, std::vector<int>(W + 1, 0));
  int value_above, instant_value, desloc, desloc_value;

  permute_values(n, values, weights);  

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 1; i <= n; i++) {
    int ui = (i * W) / n;
    int di = std::min(static_cast<int>(std::sqrt(i) * maxW), W);  

    int j_start = std::max(0, ui - di);
    int j_end = std::min(W, ui + di);

    for (int j = j_start; j <= j_end; j++) {
      value_above = knapsack_matrix[i - 1][j];
      desloc = j - weights[i - 1];
      desloc_value = (desloc < 0 || desloc > W) ? INT_MIN : knapsack_matrix[i - 1][desloc];
      instant_value = values[i - 1] + desloc_value;
      knapsack_matrix[i][j] = std::max(instant_value, value_above);
    }
  }

  instant_value = INT_MIN;
  for (int j = 0; j <= W; j++) {
    instant_value = std::max(instant_value, knapsack_matrix[n][j]);
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;

  return instant_value;
}


int default_knapsack(int W, int* weights, int* values, int n) {
  // Aloca a matriz na heap com valores inicializados em 0
  std::vector<std::vector<int>> knapsack_matrix(n + 1, std::vector<int>(W + 1, 0));
  int value_above, instant_value, desloc;

  // Loop principal de programação dinâmica
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= W; j++) {
      value_above = knapsack_matrix[i - 1][j];
      desloc = j - weights[i - 1]; 
      if (desloc >= 0) {
        instant_value = values[i - 1] + knapsack_matrix[i - 1][desloc];
        knapsack_matrix[i][j] = std::max(instant_value, value_above);
      } else {
        knapsack_matrix[i][j] = value_above;
      }
    }
  }

  // Retorna o valor ótimo da mochila
  return knapsack_matrix[n][W];
}

int main(int argc, char* argv[]){
  int n, capacity, max_weight;
  int *weights = NULL, *values = NULL;
  read_knapsack_instance(std::cin, n, capacity, max_weight, weights, values);
  auto start = std::chrono::high_resolution_clock::now();
  int result = probabilistic_knapsack(n,capacity,max_weight, weights,values);
  //int result = default_knapsack(capacity, weights, values, n);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << result << std::endl;
  std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;
}