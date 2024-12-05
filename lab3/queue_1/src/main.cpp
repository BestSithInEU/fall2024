#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/Color.hpp"
#include "../include/Queue.hpp"

void printHeader(const std::string& text) {
  std::cout << "\n" << Color::BOLD << Color::BLUE;
  std::cout << "+=" << std::string(48, '=') << "=+\n";
  std::cout << "| " << std::setw(48) << std::left << text << " |\n";
  std::cout << "+=" << std::string(48, '=') << "=+\n";
  std::cout << Color::RESET;
}

void testRottenOranges() {
  printHeader("Testing Rotten Oranges");
  std::vector<std::vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

  std::cout << "Initial grid:\n";
  for (const auto& row : grid) {
    for (int cell : row) {
      std::cout << cell << " ";
    }
    std::cout << "\n";
  }

  Queue<int> queue;
  int minutes = queue.orangesRotting(grid);
  std::cout << "\nTime to rot all oranges: " << minutes << " minutes\n";
}

void testTaskScheduler() {
  printHeader("Testing Task Scheduler");

  // Test Case 1: Tasks with required idle time
  std::vector<char> tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
  int n1 = 2;
  std::cout << "\nTest Case 1:\n";
  std::cout << "Tasks: ";
  for (char task : tasks1) {
    std::cout << task << " ";
  }
  std::cout << "\nCooldown period: " << n1 << "\n";
  Queue<int> queue1;
  int result1 = queue1.leastInterval(tasks1, n1);
  std::cout << "Minimum intervals needed: " << result1 << "\n";

  // Test Case 2: Tasks with longer cooldown
  std::vector<char> tasks2 = {'A', 'A', 'A', 'B', 'B', 'B', 'C', 'C', 'C'};
  int n2 = 3;
  std::cout << "\nTest Case 2:\n";
  std::cout << "Tasks: ";
  for (char task : tasks2) {
    std::cout << task << " ";
  }
  std::cout << "\nCooldown period: " << n2 << "\n";
  Queue<int> queue2;
  int result2 = queue2.leastInterval(tasks2, n2);
  std::cout << "Minimum intervals needed: " << result2 << "\n";

  // Test Case 3: Single task with cooldown
  std::vector<char> tasks3 = {'A', 'A', 'A'};
  int n3 = 2;
  std::cout << "\nTest Case 3:\n";
  std::cout << "Tasks: ";
  for (char task : tasks3) {
    std::cout << task << " ";
  }
  std::cout << "\nCooldown period: " << n3 << "\n";
  Queue<int> queue3;
  int result3 = queue3.leastInterval(tasks3, n3);
  std::cout << "Minimum intervals needed: " << result3 << "\n";
}

void testJumpGame() {
  printHeader("Testing Jump Game");

  std::vector<std::vector<int>> testCases = {
      {2, 3, 1, 1, 4}, {3, 2, 1, 0, 4}, {2, 0, 0}, {1, 1, 1, 1}};

  Queue<int> q;
  for (const auto& testCase : testCases) {
    std::cout << "Array: ";
    for (int num : testCase) {
      std::cout << num << " ";
    }
    std::vector<int> nums = testCase;
    std::cout << "\nCan reach end? " << (q.jumpGame(nums) ? "Yes" : "No")
              << "\n\n";
  }
}

int main() {
  printHeader("QUEUE OPERATIONS DEMONSTRATION");

  try {
    testRottenOranges();
    testTaskScheduler();
    testJumpGame();
  } catch (const std::exception& e) {
    std::cout << Color::RED << "Error: " << e.what() << Color::RESET << "\n";
  }

  printHeader("DEMONSTRATION COMPLETED");
  return 0;
}
