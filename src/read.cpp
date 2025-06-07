#include "Read.h"

void read_knapsack_instance(std::istream& cin,int& n, int& capacity, int&max_weight,int*& weights, int*& values){
  std::string line  = "", dummy;
  std::stringstream linestr;
  max_weight = INT_MIN;
  //read n and W
  getline(cin, line);
  linestr.str(line);
  linestr >> n >> capacity;
  linestr.clear();

  weights = new int[n];
  values = new int[n];


  //read values
  int aux_weight,aux_value ,i = 0;
  getline(cin, line);
  linestr.str(line);
  while (linestr >> aux_value){
    values[i] = aux_value;
    i++;
  }
  linestr.clear();

  //read weights
  i = 0;
  getline(cin, line);
  linestr.str(line);
  while (linestr >> aux_weight){
    weights[i] = aux_weight;
    if(aux_weight > max_weight){
      max_weight = aux_weight;
    }
    i++;
  }
  linestr.clear();
}