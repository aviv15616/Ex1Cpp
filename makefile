# Compiler settings
CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -g -Iinclude
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Ensure the build directory exists
$(shell mkdir -p $(BUILD_DIR))

# Source and object files (Excluding main.cpp)
SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Main program
MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o
MAIN = $(BUILD_DIR)/main

# Compile source files (excluding main.cpp)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.cpp separately
$(MAIN_OBJ): $(MAIN_SRC)
	@echo "Compiling main..."
	$(CC) $(CFLAGS) -c $< -o $@

# Link the main executable
$(MAIN): $(OBJS) $(MAIN_OBJ)
	@echo "Linking main..."
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(MAIN_OBJ)

# Run the main program
main: $(MAIN)
	@echo "Running main..."
	./$(MAIN)

# Memory leak detection using Valgrind (Only on main for now)
valgrind: $(MAIN)
	@echo "Running Valgrind..."
	valgrind --leak-check=full ./$(MAIN)

# Clean all compiled files
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)/*
