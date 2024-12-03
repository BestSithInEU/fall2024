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
  void print() const;

  Node* getNode(std::size_t index);
  Node* getLast();

  void reverseInGroups(std::size_t k);  // Task 1: Reverse the linked list in
                                        // groups of k
  void swapPairs();                     // Task 2: Swap every two adjacent nodes
  void mergeSorted(LinkedList<T>& other);  // Task 3: Merge two sorted linked
                                           // lists
  void partitionList(const T& pivot);      // Task 4: Partition the linked list
                                           // around a pivot element
};
