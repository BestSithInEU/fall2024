CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
INCLUDES = -Iinclude -Ideps
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DEPS_DIR = deps

# Color definitions
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/graph

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

deps:
	@printf "$(YELLOW)Checking dependencies...$(RESET)\n"
	@if [ ! -f "$(DEPS_DIR)/nlohmann/json.hpp" ]; then \
		printf "$(YELLOW)Downloading JSON library...$(RESET)\n"; \
		mkdir -p $(DEPS_DIR)/nlohmann; \
		curl -L https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp \
			-o $(DEPS_DIR)/nlohmann/json.hpp; \
	fi

clean:
	@printf "$(YELLOW)Cleaning up...$(RESET)\n"
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(DEPS_DIR)
	@printf "$(GREEN)Cleanup complete!$(RESET)\n"

run: $(EXECUTABLE)
	@printf "$(GREEN)Running the program...$(RESET)\n"
	@./$(EXECUTABLE)

.PHONY: all clean run deps
