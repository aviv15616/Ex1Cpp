# Author: anksilae@gmail.com


CC = g++                         
CFLAGS = -Wall -Wextra -std=c++11 -g -Iinclude
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

$(shell mkdir -p $(BUILD_DIR))

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SRC = $(SRC_DIR)/main.cpp
SRC_FILES_NO_MAIN = $(filter-out $(MAIN_SRC), $(SRC_FILES))

SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES_NO_MAIN))
MAIN_OBJ = $(BUILD_DIR)/main.o


TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_MAIN_SRC = $(TEST_DIR)/test_main.cpp
TEST_MAIN_OBJ = $(BUILD_DIR)/test_main.o
OTHER_TEST_FILES = $(filter-out $(TEST_MAIN_SRC), $(TEST_FILES))
OTHER_TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(OTHER_TEST_FILES))

MAIN_BIN = $(BUILD_DIR)/main
TEST_BIN = $(BUILD_DIR)/test_runner


all: main

main: $(MAIN_BIN)
	@echo "🚀 Running main program:"
	@./$(MAIN_BIN)

test: $(TEST_BIN)
	@echo "🔍 Running tests:"
	@./$(TEST_BIN)

valgrind: $(MAIN_BIN)
	@echo "🧠 Running main under valgrind..."
	@valgrind --leak-check=full ./$(MAIN_BIN)

valgrind-test: $(TEST_BIN)
	@echo "🧠 Running tests under valgrind..."
	@valgrind --leak-check=full ./$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)/*


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_BIN): $(SRC_OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_BIN): $(TEST_MAIN_OBJ) $(OTHER_TEST_OBJS) $(SRC_OBJS)
	$(CC) $(CFLAGS) -o $@ $^
