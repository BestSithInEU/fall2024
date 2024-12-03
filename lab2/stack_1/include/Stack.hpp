#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

#include "Color.hpp"

template <typename T>
class Stack {
 private:
  T* elements;
  int capacity;
  int topIndex;

  // Helper functions
  void insertAtBottom(const T& item);
  T removeBottom();

  // Custom struct for min-max result
  struct MinMaxResult {
    T min;
    T max;
    MinMaxResult(T minVal = T(), T maxVal = T()) : min(minVal), max(maxVal) {}
  };

  MinMaxResult findMinMaxHelper(T currentMin, T currentMax);

 public:
  explicit Stack(int initialCapacity = 10);
  ~Stack();
  Stack(const Stack& other);
  Stack& operator=(const Stack& other);

  void push(const T& value);
  T pop();
  T& peek();
  bool isEmpty() const;
  int size() const;
  void printStack(const std::string& message = "") const;

  // Lab functions
  MinMaxResult findMinMaxAndRemove();
  T removeKthFromBottom(int k);
};

namespace StackUtils {
int evaluatePostfix(const std::string& expression);
bool checkBalancedParentheses(const std::string& expression);
}  // namespace StackUtils
