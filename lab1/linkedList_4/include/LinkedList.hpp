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

  void reverseAlternateK(std::size_t k);  // Task 1: Reverse the linked list in
                                          // groups of k
  void segregateEvenOdd();  // Task 2: Segregate even and odd nodes
  void foldList();          // Task 3: Fold the linked list
  void
  sortByFrequency();  // Task 4: Sort nodes by their frequency of occurrence
};
