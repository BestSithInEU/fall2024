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
EXECUTABLE = $(BIN_DIR)/stack
TEST_EXECUTABLE = $(BIN_DIR)/test

all: $(EXECUTABLE)
	@printf "$(GREEN)Build complete! Run ./$(EXECUTABLE) to run the program.$(RESET)\n"

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@printf "$(YELLOW)Linking...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@printf "$(GREEN)Linking complete!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)Compiling $<...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_EXECUTABLE)
	@printf "$(GREEN)Running tests...$(RESET)\n"
	@./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(OBJECTS) $(OBJ_DIR)/LinkedListTest.o
	@mkdir -p $(BIN_DIR)
	@printf "$(YELLOW)Linking tests...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@printf "$(GREEN)Linking tests complete!$(RESET)\n"

$(OBJ_DIR)/LinkedListTest.o: $(TEST_DIR)/LinkedListTest.cpp
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)Compiling LinkedListTest.cpp...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(YELLOW)Cleaning up...$(RESET)\n"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@printf "$(GREEN)Cleanup complete!$(RESET)\n"

run: $(EXECUTABLE)
	@printf "$(GREEN)Running the program...$(RESET)\n"
	@./$(EXECUTABLE)

.PHONY: all clean run test
