#include "../include/LinkedList.hpp"

#include <iostream>

template <typename T> void LinkedList<T>::reverseInGroups(std::size_t k) {
  if (k <= 1 || !head)
    return;

  Node *current = head;
  Node *prevGroupEnd = nullptr;
  bool isFirstGroup = true;

  while (current) {
    Node *groupStart = current;
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
      prevGroupEnd->next = prev;
    }

    // Connect with next group
    groupStart->next = current;
    prevGroupEnd = groupStart;
  }
}

template <typename T> void LinkedList<T>::swapPairs() {
  // If list is empty or has only one node
  if (!head || !head->next)
    return;

  // Use a dummy node to handle head case easily
  Node *dummy = new Node(T());
  dummy->next = head;
  Node *prev = dummy;
  Node *current = head;

  while (current && current->next) {
    // Nodes to be swapped
    Node *first = current;
    Node *second = current->next;
    Node *nextPair = current->next->next;

    // Perform swap
    prev->next = second;
    second->next = first;
    first->next = nextPair;

    // Move pointers
    prev = first;
    current = nextPair;
  }

  // Update head
  head = dummy->next;
  delete dummy;
}

template <typename T> void LinkedList<T>::mergeSorted(LinkedList<T> &other) {
  if (other.empty())
    return;

  Node *current1 = head;
  Node *current2 = other.head;
  Node *prev = nullptr;

  // Handle head case
  if (!head || head->data >= current2->data) {
    head = current2;
    current2 = current2->next;
    head->next = current1;
    current1 = head;
  }

  while (current1 && current2) {
    if (current1->data <= current2->data) {
      prev = current1;
      current1 = current1->next;
    } else {
      Node *next2 = current2->next;
      prev->next = current2;
      current2->next = current1;
      prev = current2;
      current2 = next2;
    }
  }

  // Append remaining nodes
  if (current2) {
    prev->next = current2;
  }

  size += other.size;
  other.head = nullptr;
  other.size = 0;
}

template <typename T> void LinkedList<T>::partitionList(const T &pivot) {
  if (!head || !head->next)
    return;

  Node *lessHead = nullptr;
  Node *lessTail = nullptr;
  Node *greaterHead = nullptr;
  Node *greaterTail = nullptr;
  Node *current = head;

  while (current) {
    Node *next = current->next;
    current->next = nullptr;

    if (current->data < pivot) {
      if (!lessHead) {
        lessHead = lessTail = current;
      } else {
        lessTail->next = current;
        lessTail = current;
      }
    } else {
      if (!greaterHead) {
        greaterHead = greaterTail = current;
      } else {
        greaterTail->next = current;
        greaterTail = current;
      }
    }
    current = next;
  }

  if (!lessHead) {
    head = greaterHead;
  } else {
    head = lessHead;
    lessTail->next = greaterHead;
  }
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
