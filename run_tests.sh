run_eficency_tests() {
  local variant=$1
  local folder="results/eficiency/$variant"
  mkdir -p "$folder"
  
  local default_csv="$folder/default.csv"
  local probability_csv="$folder/probability.csv"
  
  echo "ITEM_NUM,MAX_W,W,TABLE_INSERTS,DURATION,OPT" > "$default_csv"
  echo "ITEM_NUM,MAX_W,W,TABLE_INSERTS,DURATION,OPT" > "$probability_csv"
  
  for arquivo in "./knapsack_instances/eficiency/$variant"/*; do
    ./build/knapsack "$default_csv" 1 < "$arquivo"
    ./build/knapsack "$probability_csv" 0 < "$arquivo"
  done
}

run_eficency_tests var_N
run_eficency_tests var_W
run_eficency_tests var_Wmax

run_eficency_tests "var_N(small)"
run_eficency_tests "var_W(small)"
run_eficency_tests "var_Wmax(small)"

run_probability_tests() {
  local variant=$1
  local folder="results/success_prob/"
  mkdir -p "$folder"
  
  local probability_csv="$folder/$variant.csv"

  echo "ITEM_NUM,MAX_W,W,TABLE_INSERTS,DURATION,OPT" > "$probability_csv"
  
  for arquivo in "./knapsack_instances/success_prob/$variant"/*; do
    ./build/knapsack "$probability_csv" 0 < "$arquivo"
  done
}

run_probability_tests binary_mode
run_probability_tests normal_dist
run_probability_tests normal_mode