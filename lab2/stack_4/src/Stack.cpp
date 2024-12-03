#include "../include/Stack.hpp"

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
std::string Stack<T>::decodeString(const std::string& s) const {
  Stack<char> charStack(100);  // For characters
  Stack<int> countStack(100);  // For numbers
  std::string result;
  int number = 0;

  for (char c : s) {
    if (isdigit(c)) {
      number = number * 10 + (c - '0');
    } else if (c == '[') {
      countStack.push(number);
      number = 0;
      charStack.push(c);
    } else if (c == ']') {
      std::string temp;
      // Pop until we find '['
      while (!charStack.isEmpty() && charStack.peek() != '[') {
        temp = charStack.pop() + temp;
      }

      if (!charStack.isEmpty()) {
        charStack.pop();  // Remove '['
      }

      // Repeat the string count times
      int count = countStack.isEmpty() ? 1 : countStack.pop();
      std::string repeated;
      for (int i = 0; i < count; i++) {
        repeated += temp;
      }

      // Push back the result
      for (char ch : repeated) {
        charStack.push(ch);
      }
    } else {
      charStack.push(c);
    }
  }

  // Construct final result
  while (!charStack.isEmpty()) {
    result = charStack.pop() + result;
  }

  return result;
}

template <typename T>
std::vector<int> Stack<T>::asteroidCollision(
    const std::vector<int>& asteroids) const {
  Stack<int> stack(100);

  for (int asteroid : asteroids) {
    bool destroyed = false;

    // Handle collisions only when current asteroid is moving left (negative)
    // and there are asteroids moving right (positive) in the stack
    while (!stack.isEmpty() && asteroid < 0 && stack.peek() > 0) {
      // If top asteroid is smaller, it gets destroyed
      if (stack.peek() < -asteroid) {
        stack.pop();
        continue;
      }
      // If equal size, both get destroyed
      else if (stack.peek() == -asteroid) {
        stack.pop();
        destroyed = true;
        break;
      }
      // If top asteroid is bigger, current asteroid gets destroyed
      else {
        destroyed = true;
        break;
      }
    }

    // If asteroid wasn't destroyed in any collision, add it to stack
    if (!destroyed) {
      stack.push(asteroid);
    }
  }

  // Convert stack to vector (in correct order)
  std::vector<int> result;
  Stack<int> tempStack(100);

  // First reverse the stack
  while (!stack.isEmpty()) {
    tempStack.push(stack.pop());
  }

  // Then add to result vector
  while (!tempStack.isEmpty()) {
    result.push_back(tempStack.pop());
  }

  return result;
}

template <typename T>
int Stack<T>::carFleet(int target, const std::vector<int>& position,
                       const std::vector<int>& speed) const {
  if (n == 0) return 0;

  // Create array to store cars from right to left
  Stack<double> stack(n);  // Stack to store arrival times

  // Find rightmost car
  int rightmost_idx = 0;
  for (int i = 1; i < n; i++) {
    if (position[i] > position[rightmost_idx]) {
      rightmost_idx = i;
    }
  }

  // Calculate time for rightmost car
  double time =
      (double)(target - position[rightmost_idx]) / speed[rightmost_idx];
  stack.push(time);

  // Process remaining cars from right to left
  for (int i = 0; i < n; i++) {
    if (i != rightmost_idx) {
      double curr_time = (double)(target - position[i]) / speed[i];

      // If current car takes longer time than the car in front,
      // it will form a new fleet
      if (curr_time > stack.peek()) {
        stack.push(curr_time);
      }
      // Otherwise, it will catch up and join the fleet
    }
  }

  return stack
      .size();  // Number of fleets equals number of different arrival times
}

template <typename T>
std::vector<int> Stack<T>::exclusiveTime(
    int n, const std::vector<std::string>& logs) const {
  std::vector<int> result(n, 0);
  Stack<std::pair<int, int>> stack(
      logs.size());  // Stack stores {function_id, start_time}

  for (const std::string& log : logs) {
    // Parse log entry
    size_t first_colon = log.find(':');
    size_t second_colon = log.find(':', first_colon + 1);

    int function_id = std::stoi(log.substr(0, first_colon));
    bool is_start =
        log.substr(first_colon + 1, second_colon - first_colon - 1) == "start";
    int timestamp = std::stoi(log.substr(second_colon + 1));

    if (is_start) {
      // If there's a function already running, add its execution time
      if (!stack.isEmpty()) {
        result[stack.peek().first] += timestamp - stack.peek().second;
      }
      stack.push({function_id, timestamp});
    } else {
      // End of function
      auto current = stack.pop();
      result[function_id] += timestamp - current.second + 1;

      // Update start time for the previous function
      if (!stack.isEmpty()) {
        stack.push({stack.pop().first, timestamp + 1});
      }
    }
  }

  return result;
}

namespace StackUtils {}  // namespace StackUtils

// Explicit template instantiations
template class Stack<int>;
template class Stack<double>;
template class Stack<char>;
template class Stack<std::string>;
