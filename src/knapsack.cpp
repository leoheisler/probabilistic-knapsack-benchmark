
#include "Read.h" 
#include "AuxFunct.h"
#include <cmath>

int probabilistic_knapsack(int n, int W, int maxW, int* weights, int* values){
  int knapsack_matrix[n + 1][W + 1];
  int value_above, instant_value, desloc, desloc_value;
  int ui, di;

  permute_values(n, values, weights);

  //set all values to 0
  for (int i = 0; i <= n; i++) {
    std::fill(knapsack_matrix[i], knapsack_matrix[i] + W + 1, 0);
  }

  //start loop
  for(int i = 1; i <= n; i++){
    ui = (i*W)/n;
    di = std::sqrt(i)*maxW; 
    for(int j = ui - di; j <= ui + di; j++){
      if( j >= 0 && j <= W){
        value_above =  knapsack_matrix[i - 1][j];
        desloc = j - weights[i - 1];
        if(desloc < 0 || desloc > W){
          desloc_value = INT_MIN;
        }else{
          desloc_value = knapsack_matrix[i - 1][desloc];
        }
        instant_value = values[i - 1] + desloc_value;
        knapsack_matrix[i][j] = std::max(instant_value, value_above);
      }
    }
  }
  
  //get biggest entry
  instant_value = INT_MIN;
  for (int j = 0; j <= W; j++) {
    instant_value = std::max(instant_value, knapsack_matrix[n][j]);
  }
  
  return instant_value;
}

int main(int argc, char* argv[]){
  int n, capacity, max_weight;
  int *weights = NULL, *values = NULL;
  read_knapsack_instance(std::cin, n, capacity, max_weight, weights, values);
  int result = probabilistic_knapsack(n,capacity,max_weight, weights,values);
  std::cout << result << std::endl;
}