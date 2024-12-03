#include <iomanip>
#include <iostream>
#include <string>

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

  // Create and populate a stack
  Stack<int> stack(10);
  for (int i = 1; i <= 8; i++) {
    stack.push(i);
  }

  // 1. Reverse in Groups
  std::cout << "\n"
            << Color::CYAN << "1. Reverse in Groups (k=3)" << Color::RESET
            << std::endl;
  std::cout << "Before: ";
  stack.printStack();
  stack.reverseInGroups(3);
  std::cout << "After:  ";
  stack.printStack();

  // Reset stack
  while (!stack.isEmpty()) stack.pop();
  for (int i = 1; i <= 6; i++) stack.push(i);

  // 2. Remove Alternate
  std::cout << "\n"
            << Color::CYAN << "2. Remove Alternate Elements" << Color::RESET
            << std::endl;
  std::cout << "Before: ";
  stack.printStack();
  stack.removeAlternate();
  std::cout << "After:  ";
  stack.printStack();

  // Reset stack
  while (!stack.isEmpty()) stack.pop();
  for (int i = 1; i <= 6; i++) stack.push(i);

  // 3. Interleave
  std::cout << "\n"
            << Color::CYAN << "3. Interleave Stack" << Color::RESET
            << std::endl;
  std::cout << "Before: ";
  stack.printStack();
  stack.interleave();
  std::cout << "After:  ";
  stack.printStack();

  // Reset stack
  while (!stack.isEmpty()) stack.pop();
  stack.push(4);
  stack.push(5);
  stack.push(2);
  stack.push(25);
  stack.push(10);

  // 4. Get Next Greater
  std::cout << "\n"
            << Color::CYAN << "4. Next Greater Elements" << Color::RESET
            << std::endl;
  std::cout << "Original: ";
  stack.printStack();
  Stack<int> result = stack.getNextGreater();
  std::cout << "Next Greater: ";
  result.printStack();

  printHeader("DEMONSTRATION COMPLETED");
  return 0;
}
