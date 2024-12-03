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
T Stack<T>::removeBottom() {
  // Base case: if only one element
  if (size() == 1) {
    return pop();
  }

  // Remove top element
  T temp = pop();

  // Recursively remove bottom element
  T bottom = removeBottom();

  // Push back the removed element except if it's the kth element
  push(temp);

  // Return the bottom element
  return bottom;
}

template <typename T>
T Stack<T>::removeKthFromBottom(int k) {
  if (k <= 0 || k > size()) {
    throw std::out_of_range("Invalid k value");
  }

  // If k is equal to size(), remove top element
  if (k == size()) {
    return pop();
  }

  // Remove top element
  T temp = pop();

  // Recursively remove kth element from bottom
  T kthElement = removeKthFromBottom(k);

  // Push back the removed element
  push(temp);

  // Return the kth element
  return kthElement;
}

template <typename T>
typename Stack<T>::MinMaxResult Stack<T>::findMinMaxHelper(T currentMin,
                                                           T currentMax) {
  // Base case: if stack becomes empty
  if (isEmpty()) {
    return MinMaxResult(currentMin, currentMax);
  }

  // Remove current element
  T current = pop();

  // Update min and max
  T newMin = (current < currentMin) ? current : currentMin;
  T newMax = (current > currentMax) ? current : currentMax;

  // Recursive call
  MinMaxResult result = findMinMaxHelper(newMin, newMax);

  // Push back only if current is not min or max
  if (current != result.min && current != result.max) {
    push(current);
  }

  return result;
}

template <typename T>
typename Stack<T>::MinMaxResult Stack<T>::findMinMaxAndRemove() {
  if (isEmpty()) {
    throw std::runtime_error("Stack is empty");
  }
  if (size() == 1) {
    T only = pop();
    return MinMaxResult(only, only);
  }

  // Initialize with first element
  T first = pop();
  MinMaxResult result = findMinMaxHelper(first, first);

  // If first element wasn't min or max, push it back
  if (first != result.min && first != result.max) {
    push(first);
  }

  return result;
}

namespace StackUtils {

int evaluatePostfix(const std::string& expression) {
  Stack<int> stack(expression.length());

  for (char c : expression) {
    if (isdigit(c)) {
      stack.push(c - '0');
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      if (stack.size() < 2) {
        throw std::runtime_error("Invalid expression");
      }

      int val2 = stack.pop();
      int val1 = stack.pop();

      switch (c) {
        case '+':
          stack.push(val1 + val2);
          break;
        case '-':
          stack.push(val1 - val2);
          break;
        case '*':
          stack.push(val1 * val2);
          break;
        case '/':
          if (val2 == 0) throw std::runtime_error("Division by zero");
          stack.push(val1 / val2);
          break;
      }
    }
  }

  if (stack.size() != 1) {
    throw std::runtime_error("Invalid expression");
  }

  return stack.pop();
}

bool checkBalancedParentheses(const std::string& expression) {
  Stack<char> stack(expression.length());

  for (char c : expression) {
    if (c == '(' || c == '{' || c == '[') {
      stack.push(c);
    } else if (c == ')' || c == '}' || c == ']') {
      if (stack.isEmpty()) {
        return false;
      }

      char top = stack.pop();

      if ((c == ')' && top != '(') || (c == '}' && top != '{') ||
          (c == ']' && top != '[')) {
        return false;
      }
    }
  }

  return stack.isEmpty();
}

}  // namespace StackUtils

// Explicit template instantiations
template class Stack<int>;
template class Stack<double>;
template class Stack<char>;
template class Stack<std::string>;
