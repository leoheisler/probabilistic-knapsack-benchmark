CXX = g++
CXXFLAGS = -Wall -O2 -I./src/include -std=c++20 # Atualizado para ./src

# Diretórios de saída
BUILD_DIR = build
OBJ_DIR = obj

TARGET = $(BUILD_DIR)/knapsack

SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Garante que os diretórios existam
$(shell mkdir -p $(BUILD_DIR) $(OBJ_DIR))

# Build do executável
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Build dos objetos
$(OBJ_DIR)/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)/*.o

.PHONY: clean