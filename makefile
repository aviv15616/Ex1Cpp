# Compiler settings
CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -g -Iinclude
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Ensure the build directory exists
$(shell mkdir -p $(BUILD_DIR))

# Source and object files
SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))  # Exclude main.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(BUILD_DIR)/main.o
MAIN = $(BUILD_DIR)/main

# Compile source files (excluding main.cpp)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.cpp separately
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the main executable
$(MAIN): $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(MAIN_OBJ)

# Run main program
main: $(MAIN)
	./$(MAIN)

# Memory leak detection using Valgrind (Only on main for now)
valgrind: $(MAIN)
	valgrind --leak-check=full ./$(MAIN)

# Clean all compiled files
clean:
	rm -rf $(BUILD_DIR)/*.o $(MAIN)
