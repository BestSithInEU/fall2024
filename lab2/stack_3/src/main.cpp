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

  // 1. Stack Permutation Test
  std::cout << "\n"
            << Color::CYAN << "1. Stack Permutation Test" << Color::RESET
            << std::endl;
  Stack<int> input(5);
  input.push(1);
  input.push(2);
  input.push(3);
  Stack<int> target(5);
  target.push(1);
  target.push(3);
  target.push(2);

  std::cout << "Input Stack: ";
  input.printStack();
  std::cout << "Target Stack: ";
  target.printStack();
  std::cout << "Is valid permutation: "
            << (input.stackPermutation(target) ? "Yes" : "No") << std::endl;

  // 2. Sorted Insert Test
  std::cout << "\n"
            << Color::CYAN << "2. Sorted Insert Test" << Color::RESET
            << std::endl;
  Stack<int> sortedStack(10);
  int values[] = {5, 1, 9, 2, 8};
  for (int val : values) {
    std::cout << "Inserting " << val << std::endl;
    sortedStack.sortedInsert(val);
    sortedStack.printStack("Current Stack");
  }

  // 3. Max Histogram Area Test
  std::cout << "\n"
            << Color::CYAN << "3. Max Histogram Area Test" << Color::RESET
            << std::endl;
  Stack<int> histogram(10);
  histogram.push(6);
  histogram.push(2);
  histogram.push(5);
  histogram.push(4);
  histogram.push(5);
  histogram.push(1);
  histogram.push(6);

  std::cout << "Histogram heights: ";
  histogram.printStack();
  std::cout << "Max area: " << histogram.maxHistogramArea() << std::endl;

  // 4. Max Difference Between Neighbors Test
  std::cout << "\n"
            << Color::CYAN << "4. Max Difference Between Neighbors Test"
            << Color::RESET << std::endl;
  Stack<int> numbers(10);
  numbers.push(2);
  numbers.push(8);
  numbers.push(1);
  numbers.push(5);
  numbers.push(3);

  std::cout << "Stack: ";
  numbers.printStack();
  std::cout << "Max difference between neighbors: "
            << numbers.maxDiffNeighbors() << std::endl;

  printHeader("DEMONSTRATION COMPLETED");
  return 0;
}
