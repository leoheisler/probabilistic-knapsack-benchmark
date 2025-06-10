
#include "Read.h" 
#include "AuxFunct.h"
#include <cmath>
#include <chrono> 
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>

int probabilistic_knapsack(int n, int W, int maxW, int* weights, int* values, std::ofstream& outfile) {
  std::vector<std::vector<int>> knapsack_matrix(n + 1, std::vector<int>(W + 1, 0));
  int value_above, instant_value, desloc, desloc_value, table_updt = 0;

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
      table_updt++;
    }
  }

  instant_value = INT_MIN;
  for (int j = 0; j <= W; j++) {
    instant_value = std::max(instant_value, knapsack_matrix[n][j]);
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  if(outfile.is_open()){
    outfile << n << ',';
    outfile << maxW << ',';
    outfile << W << ',';
    outfile << table_updt << ',';
    outfile << duration.count() << ',';
  }

  return instant_value;
}


int default_knapsack(int n, int W, int maxW, int* weights, int* values, std::ofstream& outfile) {
  // Aloca a matriz na heap com valores inicializados em 0
  std::vector<std::vector<int>> knapsack_matrix(n + 1, std::vector<int>(W + 1, 0));
  int value_above, instant_value, desloc, table_updt = 0;

  auto start = std::chrono::high_resolution_clock::now();
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
      table_updt++;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;

  if(outfile.is_open()){
    outfile << n << ',';
    outfile << maxW << ',';
    outfile << W << ',';
    outfile << table_updt << ',';
    outfile << duration.count() << ',';
  }

  // Retorna o valor ótimo da mochila
  return knapsack_matrix[n][W];
}

// params
// outfile argv[1]
// knapsack_type argv[2]
int main(int argc, char* argv[]){
  int knapsack_type = 0;
  std::ofstream outfile;
  if(argc >= 1){
    knapsack_type = atoi(argv[2]);
    outfile.open(argv[1], std::ios::app);
  } else {
    outfile.open(""); 
  }

  //define program vars
  int n, capacity, max_weight, opt, result;
  int *weights = NULL, *values = NULL;
  read_knapsack_instance(std::cin, n, capacity, max_weight, weights, values, opt);

  //start 
  if(knapsack_type == 0){
    result = probabilistic_knapsack(n, capacity, max_weight, weights,values, outfile);
  }else{
    result = default_knapsack(n, capacity, max_weight, weights, values, outfile);
  }

  if(outfile.is_open()){
    outfile << (result == opt) << std::endl;
  }
  outfile.close();
  std::cout << result << std::endl;
}