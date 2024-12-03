#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class Queue {
 private:
  /**
   * @brief Node structure for queue elements
   */
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* front_;  // Points to the front of the queue
  Node* rear_;   // Points to the rear of the queue
  size_t size_;  // Current number of elements in the queue

 public:
  /**
   * @brief Construct a new Queue object
   */
  Queue() : front_(nullptr), rear_(nullptr), size_(0) {}

  /**
   * @brief Destroy the Queue object and free all memory
   */
  ~Queue();

  /**
   * @brief Add an element to the rear of the queue
   * @param value The value to be added
   */
  void enqueue(const T& value);

  /**
   * @brief Remove and return the front element
   * @return T The front element
   * @throws std::runtime_error if queue is empty
   */
  T dequeue();

  /**
   * @brief Get the front element without removing it
   * @return const T& Reference to the front element
   * @throws std::runtime_error if queue is empty
   */
  const T& peek() const;

  /**
   * @brief Check if queue is empty
   * @return true if queue is empty, false otherwise
   */
  bool isEmpty() const { return size_ == 0; }

  /**
   * @brief Get the current size of the queue
   * @return size_t Number of elements in the queue
   */
  size_t size() const { return size_; }

  /**
   * @brief Clear all elements from the queue
   */
  void clear();

  int orangesRotting(std::vector<std::vector<int>>& grid);
  int leastInterval(std::vector<char>& tasks, int n);
  bool jumpGame(std::vector<int>& nums);
};

#endif /* QUEUE_HPP */
