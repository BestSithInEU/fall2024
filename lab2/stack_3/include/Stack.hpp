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
  bool stackPermutation(const Stack<T>& target) const;
  void sortedInsert(const T& value);
  int maxHistogramArea() const;
  int maxDiffNeighbors() const;
};

namespace StackUtils {}  // namespace StackUtils
