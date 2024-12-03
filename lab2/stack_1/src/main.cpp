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

void printSubHeader(const std::string& text) {
  std::cout << Color::CYAN << "\n>> " << text << Color::RESET << "\n";
  std::cout << Color::BLUE << std::string(50, '─') << Color::RESET << "\n";
}

void printResult(const std::string& label, const std::string& value) {
  std::cout << Color::YELLOW << "→ " << label << ": " << Color::GREEN << value
            << Color::RESET << std::endl;
}

void printError(const std::string& message) {
  std::cout << Color::RED << "❌ Error: " << message << Color::RESET
            << std::endl;
}

void testFindMinMaxAndRemove() {
  printHeader("FIND MIN AND MAX AND REMOVE TEST");

  // Test case 1: Regular case
  {
    printSubHeader("Test Case 1: Regular Numbers");

    Stack<int> s(5);
    s.push(3);
    s.push(1);  // min
    s.push(4);
    s.push(5);  // max
    s.push(2);

    s.printStack(Color::MAGENTA + "Initial Stack" + Color::RESET);

    try {
      auto result = s.findMinMaxAndRemove();
      std::cout << Color::CYAN << "\n📊 Results:" << Color::RESET << std::endl;
      printResult("Minimum value removed", std::to_string(result.min));
      printResult("Maximum value removed", std::to_string(result.max));

      s.printStack(Color::MAGENTA + "\nFinal Stack" + Color::RESET);
    } catch (const std::exception& e) {
      printError(e.what());
    }
  }

  // Test case 2: Duplicate elements
  {
    printSubHeader("Test Case 2: Duplicate Elements");

    Stack<int> s(6);
    s.push(3);
    s.push(1);
    s.push(5);
    s.push(1);
    s.push(5);
    s.push(2);

    s.printStack(Color::MAGENTA + "Initial Stack" + Color::RESET);

    try {
      auto result = s.findMinMaxAndRemove();
      std::cout << Color::CYAN << "\n📊 Results:" << Color::RESET << std::endl;
      printResult("Minimum value removed", std::to_string(result.min));
      printResult("Maximum value removed", std::to_string(result.max));

      s.printStack(Color::MAGENTA + "\nFinal Stack" + Color::RESET);
    } catch (const std::exception& e) {
      printError(e.what());
    }
  }
}

void testRemoveKthFromBottom() {
  printHeader("REMOVE Kth FROM BOTTOM TEST");

  Stack<int> s(5);
  for (int i = 1; i <= 5; i++) s.push(i);

  s.printStack(Color::MAGENTA + "Initial Stack" + Color::RESET);

  try {
    int k = 2;
    std::cout << Color::CYAN << "\n🎯 Operation:" << Color::RESET << std::endl;
    printResult("Attempting to remove element",
                std::to_string(k) + "th from bottom");

    int removed = s.removeKthFromBottom(k);
    printResult("Successfully removed", std::to_string(removed));

    s.printStack(Color::MAGENTA + "\nFinal Stack" + Color::RESET);
  } catch (const std::exception& e) {
    printError(e.what());
  }
}

void testEvaluatePostfix() {
  printHeader("POSTFIX EXPRESSION EVALUATION TEST");

  std::string expressions[] = {"23+", "23*", "234*+"};

  for (const auto& expr : expressions) {
    printSubHeader("Evaluating Expression: " + expr);

    try {
      int result = StackUtils::evaluatePostfix(expr);
      printResult("Expression result", std::to_string(result));
    } catch (const std::exception& e) {
      printError(e.what());
    }
  }
}

void testCheckBalancedParentheses() {
  printHeader("BALANCED PARENTHESES TEST");

  std::string expressions[] = {"{[()]}", "{[(])}", "((()))", "((()}"};

  for (const auto& expr : expressions) {
    printSubHeader("Checking Expression: " + expr);

    bool isBalanced = StackUtils::checkBalancedParentheses(expr);
    if (isBalanced) {
      std::cout << Color::GREEN << "✓ Expression is balanced" << Color::RESET
                << std::endl;
    } else {
      std::cout << Color::RED << "✗ Expression is not balanced" << Color::RESET
                << std::endl;
    }
  }
}

int main() {
  printHeader("STACK OPERATIONS TEST SUITE");

  testFindMinMaxAndRemove();
  testRemoveKthFromBottom();
  testEvaluatePostfix();
  testCheckBalancedParentheses();

  printHeader("TEST SUITE COMPLETED");
  return 0;
}
