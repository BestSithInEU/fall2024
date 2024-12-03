#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/Color.hpp"
#include "../include/Stack.hpp"

void printHeader(const std::string& text) {
  std::cout << "\n" << Color::BOLD << Color::BLUE;
  std::cout << "+=" << std::string(48, '=') << "=+\n";
  std::cout << "| " << std::setw(48) << std::left << text << " |\n";
  std::cout << "+=" << std::string(48, '=') << "=+\n";
  std::cout << Color::RESET;
}

int main() {
  printHeader("STACK OPERATIONS DEMONSTRATION");

  // 1. Decode String Test
  std::cout << "\n"
            << Color::CYAN << "1. Decode String Test" << Color::RESET
            << std::endl;
  Stack<char> decodeStack(100);
  std::vector<std::string> testCases = {
      "3[a]2[bc]",      // Expected: "aaabcbc"
      "3[a2[c]]",       // Expected: "accaccacc"
      "2[abc]3[cd]ef",  // Expected: "abcabccdcdcdef"
      "100[leetcode]"   // Stress test
  };

  for (const auto& test : testCases) {
    std::cout << "Input: " << Color::GREEN << test << Color::RESET << std::endl;
    std::cout << "Decoded: " << Color::YELLOW << decodeStack.decodeString(test)
              << Color::RESET << std::endl;
  }

  // 2. Asteroid Collision Test
  std::cout << "\n"
            << Color::CYAN << "2. Asteroid Collision Test" << Color::RESET
            << std::endl;
  Stack<int> asteroidStack(100);
  std::vector<std::vector<int>> asteroidTests = {
      {5, 10, -5},     // Expected: [5, 10]
      {8, -8},         // Expected: []
      {10, 2, -5},     // Expected: [10]
      {-2, -1, 1, 2},  // Expected: [-2, -1, 1, 2]
      {-2, -2, 1, -2}  // Expected: [-2, -2, -2]
  };

  for (const auto& asteroids : asteroidTests) {
    std::cout << "\nInput asteroids: ";
    for (int ast : asteroids) {
      if (ast > 0)
        std::cout << Color::GREEN;
      else
        std::cout << Color::RED;
      std::cout << ast << " ";
    }
    std::cout << Color::RESET;

    std::vector<int> survivors = asteroidStack.asteroidCollision(asteroids);
    std::cout << "\nSurviving asteroids: ";
    for (int survivor : survivors) {
      if (survivor > 0)
        std::cout << Color::GREEN;
      else
        std::cout << Color::RED;
      std::cout << survivor << " ";
    }
    std::cout << Color::RESET << std::endl;
  }

  // 3. Car Fleet Test
  std::cout << "\n"
            << Color::CYAN << "3. Car Fleet Test" << Color::RESET << std::endl;
  Stack<int> carStack(100);
  int target = 12;
  std::vector<int> position = {10, 8, 0, 5, 3};
  std::vector<int> speed = {2, 4, 1, 1, 3};
  std::cout << "Target: " << target << std::endl;
  std::cout << "Cars (position, speed):" << std::endl;
  for (size_t i = 0; i < position.size(); i++) {
    std::cout << "(" << position[i] << ", " << speed[i] << ") ";
  }
  std::cout << "\nNumber of fleets: "
            << carStack.carFleet(target, position, speed) << std::endl;

  // 4. Exclusive Time Test
  std::cout << "\n"
            << Color::CYAN << "4. Exclusive Time Test" << Color::RESET
            << std::endl;
  Stack<std::string> timeStack(100);
  std::vector<std::string> logs = {"0:start:0", "1:start:2", "1:end:5",
                                   "0:end:6"};
  std::cout << "Function logs:" << std::endl;
  for (const auto& log : logs) {
    std::cout << log << std::endl;
  }
  std::vector<int> times = timeStack.exclusiveTime(2, logs);
  std::cout << "Exclusive times:" << std::endl;
  for (size_t i = 0; i < times.size(); i++) {
    std::cout << "Function " << i << ": " << times[i] << std::endl;
  }

  printHeader("DEMONSTRATION COMPLETED");
  return 0;
}
