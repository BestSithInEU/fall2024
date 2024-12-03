#pragma once
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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
  std::string decodeString(const std::string& s) const;
  std::vector<int> asteroidCollision(const std::vector<int>& asteroids) const;
  int carFleet(int target, const std::vector<int>& position,
               const std::vector<int>& speed) const;
  std::vector<int> exclusiveTime(int n,
                                 const std::vector<std::string>& logs) const;
};

namespace StackUtils {}  // namespace StackUtils
