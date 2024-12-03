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

  void rotateRight(std::size_t k);  // Task 1: Rotate the linked list to the
                                    // right by k places
  bool isPalindrome();      // Task 2: Check if the linked list is a palindrome
  void removeDuplicates();  // Task 3: Remove all duplicate elements from the
                            // sorted linked list
  void sort(
      bool isAscending);  // Task 4: Sort the linked list in ascending order

  Node* getNode(std::size_t index);
  Node* getLast();
};