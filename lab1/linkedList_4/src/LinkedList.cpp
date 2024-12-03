#include "../include/LinkedList.hpp"

#include <iostream>
#include <unordered_map>

template <typename T>
void LinkedList<T>::reverseAlternateK(std::size_t k) {
  if (k <= 1 || !head || !head->next) return;

  Node* current = head;
  Node* prevTail = nullptr;
  bool shouldReverse = true;

  while (current) {
    Node* groupStart = current;
    std::size_t count = 0;

    // Count k nodes ahead
    for (count = 0; count < k && current; count++) {
      current = current->next;
    }

    if (shouldReverse && count == k) {
      // Reverse the group
      Node* prev = nullptr;
      Node* curr = groupStart;
      Node* next = nullptr;

      for (std::size_t i = 0; i < k; i++) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
      }

      if (prevTail) {
        prevTail->next = prev;
      } else {
        head = prev;
      }

      groupStart->next = current;
      prevTail = groupStart;
    } else {
      // Skip this group
      while (groupStart != current) {
        prevTail = groupStart;
        groupStart = groupStart->next;
      }
    }

    shouldReverse = !shouldReverse;
  }
}

template <typename T>
void LinkedList<T>::segregateEvenOdd() {
  if (!head || !head->next) return;

  Node* evenStart = nullptr;
  Node* evenEnd = nullptr;
  Node* oddStart = nullptr;
  Node* oddEnd = nullptr;
  Node* current = head;

  while (current) {
    if (current->data % 2 == 0) {
      if (!evenStart) {
        evenStart = evenEnd = current;
      } else {
        evenEnd->next = current;
        evenEnd = current;
      }
    } else {
      if (!oddStart) {
        oddStart = oddEnd = current;
      } else {
        oddEnd->next = current;
        oddEnd = current;
      }
    }
    current = current->next;
  }

  if (!evenStart || !oddStart) return;

  evenEnd->next = oddStart;
  oddEnd->next = nullptr;
  head = evenStart;
}

template <typename T>
void LinkedList<T>::foldList() {
  if (!head || !head->next) return;

  // Find middle using slow and fast pointers
  Node* slow = head;
  Node* fast = head;
  Node* prev = nullptr;

  while (fast && fast->next) {
    fast = fast->next->next;
    prev = slow;
    slow = slow->next;
  }

  if (!prev) return;  // List too short

  // Split the list into two halves
  Node* second = prev->next;
  prev->next = nullptr;

  // Reverse the second half
  Node* curr = second;
  prev = nullptr;

  while (curr) {
    Node* next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  // Merge the two halves
  Node* first = head;
  second = prev;

  while (first && second) {
    Node* firstNext = first->next;
    Node* secondNext = second->next;

    first->next = second;
    if (firstNext) {  // Check if there are more nodes to process
      second->next = firstNext;
    }

    first = firstNext;
    second = secondNext;
  }
}

template <typename T>
void LinkedList<T>::sortByFrequency() {
  if (!head || !head->next) return;

  // Step 1: Count frequencies
  std::unordered_map<T, int> freq;
  Node* current = head;
  while (current) {
    freq[current->data]++;
    current = current->next;
  }

  // Step 2: Create a new list with sorted elements
  Node* newHead = nullptr;
  Node* newTail = nullptr;

  // Find max frequency in current iteration
  while (!freq.empty()) {
    T maxFreqValue = freq.begin()->first;
    int maxFreq = freq.begin()->second;

    // Find value with highest frequency
    for (const auto& pair : freq) {
      if (pair.second > maxFreq ||
          (pair.second == maxFreq && pair.first < maxFreqValue)) {
        maxFreqValue = pair.first;
        maxFreq = pair.second;
      }
    }

    // Add nodes with maxFreqValue
    for (int i = 0; i < maxFreq; i++) {
      Node* newNode = new Node(maxFreqValue);
      if (!newHead) {
        newHead = newTail = newNode;
      } else {
        newTail->next = newNode;
        newTail = newNode;
      }
    }

    // Remove processed value from frequency map
    freq.erase(maxFreqValue);
  }

  // Clean up old list
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }

  // Update head to new sorted list
  head = newHead;
}

/**
 * @brief Default constructor
 */
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

/**
 * @brief Destructor to clean up allocated memory
 */
template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
}

/**
 * @brief Insert a new element at the front of the list
 * @param value The value to insert
 */
template <typename T>
void LinkedList<T>::push_front(const T& value) {
  Node* newNode = new Node(value);
  newNode->next = head;
  head = newNode;
  ++size;
}

/**
 * @brief Insert a new element at the back of the list
 * @param value The value to insert
 */
template <typename T>
void LinkedList<T>::push_back(const T& value) {
  Node* newNode = new Node(value);

  if (!head) {
    head = newNode;
  } else {
    Node* current = head;
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
template <typename T>
void LinkedList<T>::pop_front() {
  if (!head) return;

  Node* temp = head;
  head = head->next;
  delete temp;
  --size;
}

/**
 * @brief Get the value at the front of the list
 * @return Reference to the first element
 * @throw std::runtime_error if the list is empty
 */
template <typename T>
T& LinkedList<T>::front() {
  if (!head) throw std::runtime_error("List is empty");
  return head->data;
}

/**
 * @brief Get the value at the front of the list (const version)
 * @return Const reference to the first element
 * @throw std::runtime_error if the list is empty
 */
template <typename T>
const T& LinkedList<T>::front() const {
  if (!head) throw std::runtime_error("List is empty");
  return head->data;
}

/**
 * @brief Check if the list is empty
 * @return true if the list is empty, false otherwise
 */
template <typename T>
bool LinkedList<T>::empty() const {
  return head == nullptr;
}

/**
 * @brief Get the current size of the list
 * @return Number of elements in the list
 */
template <typename T>
std::size_t LinkedList<T>::get_size() const {
  return size;
}

/**
 * @brief Remove all elements from the list
 */
template <typename T>
void LinkedList<T>::clear() {
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
  size = 0;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(std::size_t index) {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }

  Node* current = head;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->next;
  }

  return current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getLast() {
  if (empty()) {
    return nullptr;
  }

  Node* current = head;
  while (current->next) {
    current = current->next;
  }

  return current;
}

template <typename T>
void LinkedList<T>::print() const {
  Node* current = head;
  while (current) {
    std::cout << current->data << " -> ";
    current = current->next;
  }
  std::cout << "nullptr" << std::endl;
}

template class LinkedList<int>;
