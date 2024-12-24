CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
INCLUDES = -I./include -I./third_party
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test
DEPS_DIR = third_party

# Color definitions
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/chess_game

all: deps $(EXECUTABLE)
	@printf "$(GREEN)Build complete! Run ./$(EXECUTABLE) to start the project.$(RESET)\n"

deps:
	@printf "$(YELLOW)Checking dependencies...$(RESET)\n"
	@if [ ! -f "$(DEPS_DIR)/nlohmann/json.hpp" ]; then \
		printf "$(YELLOW)Downloading JSON library...$(RESET)\n"; \
		mkdir -p $(DEPS_DIR)/nlohmann; \
		curl -L https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp \
			-o $(DEPS_DIR)/nlohmann/json.hpp; \
	fi

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@printf "$(YELLOW)Linking...$(RESET)\n"
	@$(CXX) $(OBJECTS) -o $@
	@printf "$(GREEN)Linking complete!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)Compiling $<...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(YELLOW)Cleaning up...$(RESET)\n"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@printf "$(GREEN)Cleanup complete!$(RESET)\n"

distclean: clean
	@printf "$(YELLOW)Removing dependencies...$(RESET)\n"
	@rm -rf $(DEPS_DIR)
	@printf "$(GREEN)Dependencies removed!$(RESET)\n"

run: $(EXECUTABLE)
	@printf "$(GREEN)Running the project with chess_pieces.json...$(RESET)\n"
	@./$(EXECUTABLE) data/chess_pieces.json

run_fantasy: $(EXECUTABLE)
	@printf "$(GREEN)Running the project with fantasy_chess.json...$(RESET)\n"
	@./$(EXECUTABLE) data/fantasy_chess.json

.PHONY: all clean distclean run deps
