#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

int default_knapsack(int W, const vector<int>& wt, const vector<int>& val, int n){
  int knapsack_matrix[n + 1][W + 1];
  int value_above, instant_value, desloc;

  //first line is 0
  std::fill(knapsack_matrix[0], knapsack_matrix[0] + W + 1, 0);

  //start loop
  for(int i = 1; i <= n; i++){
    for(int j = 0; j <= W; j++){
      value_above =  knapsack_matrix[i - 1][j];
      desloc = j - wt[i - 1]; 
      if (desloc >= 0){
        instant_value = val[i - 1] + knapsack_matrix[i - 1][desloc];
        knapsack_matrix[i][j] = std::max(instant_value, value_above);
      }else{
        knapsack_matrix[i][j] = value_above;
      }
    }
  }
  //get last entry
  return knapsack_matrix[n][W];
}

void parse_args(int argc, char* argv[], 
  int& n, int& W, pair<int,int>& v_range, 
  pair<int,int>& w_range, bool& normal_mode) {
  // Set default values
  n = 20;
  W = 100;
  v_range = {1, 50};
  w_range = {1, 20};
  normal_mode = false;

  // Parse command line arguments
  for (int i = 1; i < argc; i++) {
    string arg = argv[i];
    if (arg == "-n" && i+1 < argc) {
      n = stoi(argv[++i]);
    } else if (arg == "-W" && i+1 < argc) {
      W = stoi(argv[++i]);
    } else if (arg == "-v" && i+2 < argc) {
      v_range.first = stoi(argv[++i]);
      v_range.second = stoi(argv[++i]);
    } else if (arg == "-w" && i+2 < argc) {
      w_range.first = stoi(argv[++i]);
      w_range.second = stoi(argv[++i]);
    } else if (arg == "--normal-mode") {
      normal_mode = true;
    }
  }
}

//OPTIONAL_VALUES:
// -n, [int], number of items 
// -W, [int], w max
// -v v0 vn, [int,int], range for values in normal distribution
// -w w0 wn , [int,int], range for weights in normal distribution
// --normal-mode, values goes to 1 ~ n, weights set in 1

//DEFAULT VALUES:
// n = 20
// W = 100
// vi = normal distr (1,50)
// wi = normal distr (1,20)
// example:
// ./knapsack_generator -n 15 -W 50 -v 10 100 -w 5 25
// ./knapsack_generator --normal-mode -n 10 -W 20
int main(int argc, char* argv[]) {
  mt19937 rng(time(0));
  
  //params
  int n, W;
  pair<int, int> v_range, w_range;
  bool normal_mode;
  
  //parser
  parse_args(argc, argv, n, W, v_range, w_range, normal_mode);

  vector<int> values(n);
  vector<int> weights(n);
  
  if (normal_mode) {
    for (int i = 0; i < n; i++) {
      values[i] = i + 1;
      weights[i] = 1;
    }
  } else {
    // Random values and weights within specified ranges
    uniform_int_distribution<int> v_dist(v_range.first, v_range.second);
    uniform_int_distribution<int> w_dist(w_range.first, w_range.second);
    
    for (int i = 0; i < n; i++) {
      values[i] = v_dist(rng);
      weights[i] = w_dist(rng);
    }
  }
  
  int optimal = default_knapsack(W, weights, values, n);
  
  cout << n << " " << W << endl;
  
  for (int i = 0; i < n; i++) {
      cout << values[i];
      if (i < n - 1) cout << " ";
  }
  cout << endl;
  
  for (int i = 0; i < n; i++) {
      cout << weights[i];
      if (i < n - 1) cout << " ";
  }
  cout << endl;
  cout << optimal << endl;
  return 0;
}