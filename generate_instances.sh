#!/bin/bash

# Verifica se o gerador existe
if [[ ! -x ./build/generator ]]; then
  echo "Erro: ./build/generator não encontrado ou sem permissão de execução."
  exit 1
fi

# Criação das pastas
mkdir -p "knapsack_instances/eficiency/var_N"
mkdir -p "knapsack_instances/eficiency/var_W"
mkdir -p "knapsack_instances/eficiency/var_Wmax"

##############################
# Variação no número de itens
##############################

echo "Creating 100 normal_dist instances varying N..."

instance_prefix="knapsack_instances/eficiency/var_N/"
fixed_W=10000
fixed_wmax=500
start_n=100
jump_n=100

for ((i = 1; i <= 100; i++)); do
  instance_name="${instance_prefix}${start_n}.txt"
  echo "Creating instance: N=${start_n}"

  ./build/generator -W "$fixed_W" -w 0 "$fixed_wmax" -n "$start_n" > "$instance_name"

  start_n=$((start_n + jump_n))
done

##############################
# Variação no peso máximo dos itens
##############################

echo "Creating 100 normal_dist instances varying wmax..."

instance_prefix="knapsack_instances/eficiency/var_Wmax/"
fixed_W=10000
fixed_n=5000
start_wmax=100
jump_wmax=100

for ((i = 1; i <= 100; i++)); do
  instance_name="${instance_prefix}${start_wmax}.txt"
  echo "Creating instance: wmax=${start_wmax}"

  ./build/generator -W "$fixed_W" -w 0 "$start_wmax" -n "$fixed_n" > "$instance_name"

  start_wmax=$((start_wmax + jump_wmax))
done

##############################
# Variação na capacidade da mochila
##############################

echo "Creating 100 normal_dist instances varying W..."

instance_prefix="knapsack_instances/eficiency/var_W/"
start_W=10000
fixed_n=5000
fixed_wmax=500
jump_W=100

for ((i = 1; i <= 100; i++)); do
  instance_name="${instance_prefix}${start_W}.txt"
  echo "Creating instance: W=${start_W}"

  ./build/generator -W "$start_W" -w 0 "$fixed_wmax" -n "$fixed_n" > "$instance_name"

  start_W=$((start_W - jump_W))
done

######################################################################
# probability instances
######################################################################

# Criação das pastas
mkdir -p "knapsack_instances/success_prob/binary_mode"
mkdir -p "knapsack_instances/success_prob/normal_dist"
mkdir -p "knapsack_instances/success_prob/normal_mode"

##############################
# Binary_data
##############################

echo "Creating 100 binary_mode instances..."

instance_prefix="knapsack_instances/success_prob/binary_mode/"
start_n=100
jump_n=100

for ((i = 1; i <= 100; i++)); do
  instance_name="${instance_prefix}${start_n}.txt"
  echo "Creating binary_mode instance: N=${start_n}"

  ./build/generator --binary-mode -n "$start_n" > "$instance_name"

  start_n=$((start_n + jump_n))
done


##############################
# Normal_mode data
##############################

echo "Creating 100 normal_mode instances..."

instance_prefix="knapsack_instances/success_prob/normal_mode/"
start_n=100
jump_n=100

for ((i = 1; i <= 100; i++)); do
  instance_name="${instance_prefix}${start_n}.txt"
  echo "Creating normal_mode instance: N=${start_n}"

  ./build/generator --normal-mode -n "$start_n" > "$instance_name"

  start_n=$((start_n + jump_n))
done


##############################
# Normal_dist aleatória (parâmetros aleatórios)
##############################

echo "Creating 100 normal_dist instances with random N, wmax, and W..."

instance_prefix="knapsack_instances/success_prob/normal_dist/"

for ((i = 1; i <= 100; i++)); do
  n=$((RANDOM % 10001))                   # n entre 0 e 10000
  maxw=$(((RANDOM % (2000 - 100 + 1)) + 100))  # wmax entre 100 e 2000
  W=$(((RANDOM % (10000 - maxw + 1)) + maxw))  # W entre wmax e 10000

  instance_name="${instance_prefix}inst_${i}_n${n}_w${maxw}_W${W}.txt"
  echo "Creating normal_dist instance: N=${n}, wmax=${maxw}, W=${W}"

  ./build/generator -W "$W" -w 0 "$maxw" -n "$n" > "$instance_name"
done
