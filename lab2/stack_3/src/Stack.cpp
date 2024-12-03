#include "../include/Stack.hpp"

#include <cctype>
#include <iostream>

template <typename T>
Stack<T>::Stack(int initialCapacity) : capacity(initialCapacity), topIndex(-1) {
  elements = new T[capacity];
}

template <typename T>
Stack<T>::~Stack() {
  delete[] elements;
}

template <typename T>
Stack<T>::Stack(const Stack& other)
    : capacity(other.capacity), topIndex(other.topIndex) {
  elements = new T[capacity];
  for (int i = 0; i <= topIndex; i++) {
    elements[i] = other.elements[i];
  }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  if (this != &other) {
    delete[] elements;
    capacity = other.capacity;
    topIndex = other.topIndex;
    elements = new T[capacity];
    for (int i = 0; i <= topIndex; i++) {
      elements[i] = other.elements[i];
    }
  }
  return *this;
}

template <typename T>
void Stack<T>::push(const T& value) {
  if (topIndex + 1 >= capacity) {
    // Double the capacity when full
    T* newElements = new T[capacity * 2];
    for (int i = 0; i <= topIndex; i++) {
      newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity *= 2;
  }
  elements[++topIndex] = value;
}

template <typename T>
T Stack<T>::pop() {
  if (isEmpty()) {
    throw std::runtime_error("Stack is empty");
  }
  return elements[topIndex--];
}

template <typename T>
T& Stack<T>::peek() {
  if (isEmpty()) {
    throw std::runtime_error("Stack is empty");
  }
  return elements[topIndex];
}

template <typename T>
bool Stack<T>::isEmpty() const {
  return topIndex == -1;
}

template <typename T>
int Stack<T>::size() const {
  return topIndex + 1;
}

template <typename T>
void Stack<T>::printStack(const std::string& message) const {
  if (!message.empty()) {
    std::cout << message << ": ";
  }

  if (isEmpty()) {
    std::cout << Color::RED << "Empty stack" << Color::RESET << std::endl;
    return;
  }

  Stack<T> temp(*this);
  std::cout << Color::CYAN << "Bottom -> " << Color::GREEN;
  while (!temp.isEmpty()) {
    std::cout << temp.pop() << " ";
  }
  std::cout << Color::CYAN << "<- Top" << Color::RESET << std::endl;
}

template <typename T>
bool Stack<T>::stackPermutation(const Stack<T>& target) const {
  if (size() != target.size()) return false;

  Stack<T> tempInput(*this);    // Copy of input stack
  Stack<T> tempTarget(target);  // Copy of target stack
  Stack<T> aux(capacity);       // Auxiliary stack

  // Reverse stacks to match original order
  Stack<T> input(capacity);
  Stack<T> targetStack(capacity);
  while (!tempInput.isEmpty()) input.push(tempInput.pop());
  while (!tempTarget.isEmpty()) targetStack.push(tempTarget.pop());

  while (!input.isEmpty()) {
    T current = input.pop();

    if (current == targetStack.peek()) {
      targetStack.pop();
      while (!aux.isEmpty() && aux.peek() == targetStack.peek()) {
        aux.pop();
        targetStack.pop();
      }
    } else {
      aux.push(current);
    }
  }

  return (aux.isEmpty() && targetStack.isEmpty());
}

template <typename T>
void Stack<T>::sortedInsert(const T& value) {
  if (isEmpty() || value >= peek()) {
    push(value);
    return;
  }

  T temp = pop();
  sortedInsert(value);
  push(temp);
}

template <typename T>
int Stack<T>::maxHistogramArea() const {
  if (isEmpty()) return 0;

  Stack<int> positions(capacity);
  Stack<T> heights(capacity);
  int maxArea = 0;
  int i = 0;

  // Process all bars
  while (i <= topIndex) {
    // If stack is empty or current bar is higher, push
    if (positions.isEmpty() || elements[positions.peek()] <= elements[i]) {
      positions.push(i);
      i++;
    } else {
      // Calculate area with the top bar as smallest
      int top = positions.pop();
      int width = positions.isEmpty() ? i : i - positions.peek() - 1;
      int area = elements[top] * width;
      maxArea = std::max(maxArea, area);
    }
  }

  // Process remaining bars in stack
  while (!positions.isEmpty()) {
    int top = positions.pop();
    int width = positions.isEmpty() ? i : i - positions.peek() - 1;
    int area = elements[top] * width;
    maxArea = std::max(maxArea, area);
  }

  return maxArea;
}

template <typename T>
int Stack<T>::maxDiffNeighbors() const {
  if (size() < 2) return 0;  // Need at least 2 elements

  T maxDiff = 0;
  // Compare each adjacent pair
  for (int i = 0; i < topIndex; i++) {
    T diff = std::abs(elements[i] - elements[i + 1]);
    maxDiff = std::max(maxDiff, diff);
  }

  return maxDiff;
}

namespace StackUtils {}  // namespace StackUtils

// Explicit template instantiations
template class Stack<int>;
template class Stack<double>;
