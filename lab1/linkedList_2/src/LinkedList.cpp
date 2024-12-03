#include "../include/LinkedList.hpp"

#include <iostream>

template <typename T> void LinkedList<T>::rotateRight(std::size_t k) {
  if (empty() || k == 0 || k % size == 0)
    return;

  k = k % size;

  Node *current = head;
  Node *newTail = nullptr;
  for (std::size_t i = 0; i < size - k - 1; ++i) {
    current = current->next;
  }

  newTail = current;
  Node *newHead = current->next;

  // Find the last node
  Node *last = newHead;
  while (last->next) {
    last = last->next;
  }

  // Update the last node's next to the current head
  last->next = head;

  // Update the new tail's next to nullptr
  newTail->next = nullptr;

  // Update the head to the new head
  head = newHead;
}

template <typename T> bool LinkedList<T>::isPalindrome() {
  if (empty() || head->next == nullptr)
    return true;

  Node *slow = head;
  Node *fast = head;
  Node *prev = nullptr;

  while (fast && fast->next) {
    fast = fast->next->next;
    Node *next = slow->next;
    slow->next = prev;
    prev = slow;
    slow = next;
  }

  if (fast)
    slow = slow->next;

  while (slow) {
    if (slow->data != prev->data)
      return false;
    slow = slow->next;
    prev = prev->next;
  }

  return true;
}

template <typename T> void LinkedList<T>::removeDuplicates() {
  if (empty() || head->next == nullptr)
    return;

  Node *current = head;
  while (current->next) {
    if (current->data == current->next->data) {
      Node *temp = current->next;
      current->next = current->next->next;
      delete temp;
      --size;
    } else {
      current = current->next;
    }
  }
}

template <typename T> void LinkedList<T>::sort(bool isAscending) {
  if (empty() || head->next == nullptr)
    return;

  bool swapped;
  Node *current;
  Node *last = nullptr;

  do {
    swapped = false;
    current = head;

    while (current->next != last) {
      if ((isAscending && current->data > current->next->data) ||
          (!isAscending && current->data < current->next->data)) {
        // Swap nodes
        T temp = current->data;
        current->data = current->next->data;
        current->next->data = temp;
        swapped = true;
      }
      current = current->next;
    }
    last = current;
  } while (swapped);
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

template <typename T> void LinkedList<T>::print() const {
  Node *current = head;
  while (current) {
    std::cout << current->data << " -> ";
    current = current->next;
  }
  std::cout << "nullptr" << std::endl;
}

template class LinkedList<int>;
