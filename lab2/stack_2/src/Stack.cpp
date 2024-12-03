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
void Stack<T>::reverseInGroups(int k) {
  if (isEmpty() || k <= 1) return;

  Stack<T> tempStack(capacity);
  Stack<T> auxStack(capacity);

  // First, transfer all elements to auxStack to maintain order
  while (!isEmpty()) {
    auxStack.push(pop());
  }

  // Now process k elements at a time
  while (!auxStack.isEmpty()) {
    Stack<T> groupStack(k);  // Stack for current group
    int count = std::min(k, auxStack.size());

    // Get k elements for current group
    for (int i = 0; i < count; i++) {
      groupStack.push(auxStack.pop());
    }

    // Push reversed group back to original stack
    while (!groupStack.isEmpty()) {
      push(groupStack.pop());
    }
  }
}

template <typename T>
void Stack<T>::removeAlternate() {
  if (size() <= 1) return;

  Stack<T> tempStack(capacity);
  bool shouldRemove = false;  // Start with keeping first element

  // Move elements to temp stack (reverses order)
  while (!isEmpty()) {
    T current = pop();
    if (!shouldRemove) {
      tempStack.push(current);
    }
    shouldRemove = !shouldRemove;
  }

  // Move elements back to original stack (restores order)
  while (!tempStack.isEmpty()) {
    push(tempStack.pop());
  }
}

template <typename T>
void Stack<T>::interleave() {
  if (size() <= 2) return;

  int halfSize = size() / 2;
  Stack<T> firstHalf(halfSize);
  Stack<T> secondHalf(halfSize);

  // Split into two halves
  for (int i = 0; i < halfSize; i++) {
    secondHalf.push(pop());
  }
  for (int i = 0; i < halfSize; i++) {
    firstHalf.push(pop());
  }

  // Interleave elements
  while (!firstHalf.isEmpty()) {
    push(firstHalf.pop());  // from first half
    if (!secondHalf.isEmpty()) {
      push(secondHalf.pop());  // from second half
    }
  }
}

template <typename T>
Stack<T> Stack<T>::getNextGreater() const {
  Stack<T> result(capacity);
  Stack<T> tempStack(capacity);

  // Copy original stack
  Stack<T> elements(capacity);
  for (int i = 0; i <= topIndex; i++) {
    elements.push(this->elements[i]);
  }

  // For each element, find next greater
  while (!elements.isEmpty()) {
    T current = elements.pop();

    // Remove elements from tempStack and find next greater
    bool foundGreater = false;
    Stack<T> auxStack(capacity);

    while (!elements.isEmpty()) {
      T next = elements.pop();
      if (!foundGreater && next > current) {
        result.push(next);
        foundGreater = true;
      }
      auxStack.push(next);
    }

    // If no greater element found
    if (!foundGreater) {
      result.push(T());  // Use default value (0 for int)
    }

    // Restore elements
    while (!auxStack.isEmpty()) {
      elements.push(auxStack.pop());
    }

    tempStack.push(current);
  }

  // Reverse result to match original order
  Stack<T> finalResult(capacity);
  while (!result.isEmpty()) {
    finalResult.push(result.pop());
  }

  return finalResult;
}

namespace StackUtils {}  // namespace StackUtils

// Explicit template instantiations
template class Stack<int>;
template class Stack<double>;
template class Stack<char>;
template class Stack<std::string>;
