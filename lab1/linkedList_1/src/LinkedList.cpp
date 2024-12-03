#include "../include/LinkedList.hpp"

#include <iostream>

template <typename T> void LinkedList<T>::reverseInGroups(std::size_t k) {
  if (k <= 1 || !head)
    return;

  Node *current = head;
  Node *prevFirst = nullptr;
  bool isFirstGroup = true;

  while (current) {
    Node *first = current;
    Node *prev = nullptr;
    Node *next = nullptr;
    std::size_t count = 0;

    // Reverse k nodes
    while (current && count < k) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
      count++;
    }

    // Connect with previous group
    if (isFirstGroup) {
      head = prev;
      isFirstGroup = false;
    } else {
      prevFirst->next = prev;
    }

    first->next = current;
    prevFirst = first;
  }
}

template <typename T> T &LinkedList<T>::findKthFromEnd(std::size_t k) {
  if (!head || k == 0)
    throw std::out_of_range("Invalid k or empty list");

  Node *fast = head;
  Node *slow = head;

  // Move fast k nodes ahead
  for (std::size_t i = 0; i < k; i++) {
    if (!fast)
      throw std::out_of_range("k is larger than list length");
    fast = fast->next;
  }

  // Move both pointers until fast reaches end
  while (fast) {
    slow = slow->next;
    fast = fast->next;
  }

  return slow->data;
}

template <typename T> bool LinkedList<T>::detectAndRemoveLoop() {
  if (!head || !head->next)
    return false;

  Node *slow = head;
  Node *fast = head;
  bool hasLoop = false;

  // Detect loop using Floyd's algorithm
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      hasLoop = true;
      break;
    }
  }

  if (!hasLoop)
    return false;

  // Find loop starting point
  slow = head;
  while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }

  // Find last node in loop
  Node *loopNode = slow;
  while (fast->next != loopNode) {
    fast = fast->next;
  }

  // Remove loop
  fast->next = nullptr;
  return true;
}

template <typename T> void LinkedList<T>::print() const {
  Node *current = head;
  while (current) {
    std::cout << current->data << " -> ";
    current = current->next;
  }
  std::cout << "nullptr" << std::endl;
}

/**
 * @brief Default constructor
 */
template <typename T> LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

/**
 * @brief Destructor to clean up allocated memory
 */
template <typename T> LinkedList<T>::~LinkedList() { clear(); }

/**
 * @brief Insert a new element at the front of the list
 * @param value The value to insert
 */
template <typename T> void LinkedList<T>::push_front(const T &value) {
  Node *newNode = new Node(value);
  newNode->next = head;
  head = newNode;
  ++size;
}

/**
 * @brief Insert a new element at the back of the list
 * @param value The value to insert
 */
template <typename T> void LinkedList<T>::push_back(const T &value) {
  Node *newNode = new Node(value);

  if (!head) {
    head = newNode;
  } else {
    Node *current = head;
    while (current->next) {
      current = current->next;
    }
    current->next = newNode;
  }
  ++size;
}

/**
 * @brief Remove the first element from the list
 */
template <typename T> void LinkedList<T>::pop_front() {
  if (!head)
    return;

  Node *temp = head;
  head = head->next;
  delete temp;
  --size;
}

/**
 * @brief Get the value at the front of the list
 * @return Reference to the first element
 * @throw std::runtime_error if the list is empty
 */
template <typename T> T &LinkedList<T>::front() {
  if (!head)
    throw std::runtime_error("List is empty");
  return head->data;
}

/**
 * @brief Get the value at the front of the list (const version)
 * @return Const reference to the first element
 * @throw std::runtime_error if the list is empty
 */
template <typename T> const T &LinkedList<T>::front() const {
  if (!head)
    throw std::runtime_error("List is empty");
  return head->data;
}

/**
 * @brief Check if the list is empty
 * @return true if the list is empty, false otherwise
 */
template <typename T> bool LinkedList<T>::empty() const {
  return head == nullptr;
}

/**
 * @brief Get the current size of the list
 * @return Number of elements in the list
 */
template <typename T> std::size_t LinkedList<T>::get_size() const {
  return size;
}

/**
 * @brief Remove all elements from the list
 */
template <typename T> void LinkedList<T>::clear() {
  while (head) {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  size = 0;
}

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::getNode(std::size_t index) {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }

  Node *current = head;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->next;
  }

  return current;
}

template <typename T> typename LinkedList<T>::Node *LinkedList<T>::getLast() {
  if (empty()) {
    return nullptr;
  }

  Node *current = head;
  while (current->next) {
    current = current->next;
  }

  return current;
}

template <typename T>
void LinkedList<T>::createCycle(std::size_t cycleStartIndex) {
  if (cycleStartIndex >= size) {
    throw std::out_of_range("Cycle start index out of range");
  }

  Node *cycleNode = getNode(cycleStartIndex);
  getLast()->next = cycleNode;
}

template class LinkedList<int>;
