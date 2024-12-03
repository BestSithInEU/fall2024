#pragma once

#include <cstddef>

/**
 * @brief A templated singly linked list implementation
 * @tparam T The type of elements stored in the list
 */
template <typename T>
class LinkedList {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;        // Pointer to the first node
  std::size_t size;  // Current size of the list

 public:
  LinkedList();
  ~LinkedList();

  // Basic operations
  void push_front(const T& value);
  void push_back(const T& value);
  void pop_front();
  T& front();
  const T& front() const;
  bool empty() const;
  std::size_t get_size() const;
  void clear();

  void reverseInGroups(
      std::size_t k);  // Task 1: Reverse the list in groups of K nodes
  T& findKthFromEnd(
      std::size_t k);          // Task 2: Find kth node from end in one pass
  bool detectAndRemoveLoop();  // Task 3: Detect and remove loop if exists
  void print() const;          // Task 4: Print the list

  Node* getNode(std::size_t index);
  Node* getLast();

  void createCycle(
      std::size_t cycleStartIndex);  // New function to create a cycle
};
