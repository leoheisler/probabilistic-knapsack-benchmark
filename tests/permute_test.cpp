#include <random>
#include <algorithm>
#include <iostream>
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
void print_array(int n, int* vector) {

  std::cout << "[ ";
  for (int i = 0; i < n; ++i) {
    std::cout << vector[i] << " ";
  }
  std::cout << "]" << std::endl;
}

int main(){
  int n = 6;
  int w[] = {1, 2, 3, 4, 5, 6}; 
  int v[] = {1, 2, 3, 4, 5, 6}; 

  permute_values(n,v,w);
  print_array(n,v);
  print_array(n,w);
}