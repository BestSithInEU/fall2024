CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
INCLUDES = -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

# Color definitions
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/linkedlist
TEST_EXECUTABLE = $(BIN_DIR)/test

all: $(EXECUTABLE)
	@echo -e "$(GREEN)Build complete! Run ./$(EXECUTABLE) to run the program.$(RESET)"

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@echo -e "$(YELLOW)Linking...$(RESET)"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo -e "$(GREEN)Linking complete!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@echo -e "$(CYAN)Compiling $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_EXECUTABLE)
	@echo -e "$(GREEN)Running tests...$(RESET)"
	@./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(OBJECTS) $(OBJ_DIR)/LinkedListTest.o
	@mkdir -p $(BIN_DIR)
	@echo -e "$(YELLOW)Linking tests...$(RESET)"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo -e "$(GREEN)Linking tests complete!$(RESET)"

$(OBJ_DIR)/LinkedListTest.o: $(TEST_DIR)/LinkedListTest.cpp
	@mkdir -p $(OBJ_DIR)
	@echo -e "$(CYAN)Compiling LinkedListTest.cpp...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(YELLOW)Cleaning up...$(RESET)"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo -e "$(GREEN)Cleanup complete!$(RESET)"

run: $(EXECUTABLE)
	@echo -e "$(GREEN)Running the program...$(RESET)"
	@./$(EXECUTABLE)

.PHONY: all clean run test
