#ifndef AUXFUNCTS_H
#define AUXFUNCTS_H
  #include <iostream>
  #include <vector>
  #include <random>
  #include <algorithm>
  
  void print_array(int n, int* vector);
  void print_matrix(int i, int j, int**matrix);
  bool is_in_bounds(int i, int W);
  void permute_values(int n, int* values, int* weights);
#endif //AUXFUNCTS.H