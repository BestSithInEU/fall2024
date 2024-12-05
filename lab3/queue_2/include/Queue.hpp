#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations of all structs
struct Result;
struct Task;
struct PacketInfo;
struct OrderRequest;
struct ProcessorState;
struct OrderInfo;
struct Packet;

// Struct definitions
struct Result {
  int id;
  int time;
  int resourceId;
  Result(int i, int t, int r) : id(i), time(t), resourceId(r) {}
};

struct Task {
  int priority;
  int duration;
  int id;
  Task(int p, int d, int i) : priority(p), duration(d), id(i) {}
};

struct PacketInfo {
  int destination;
  int size;
  int priority;
  int arrival_time;
  PacketInfo(int dest, int sz, int prio, int arr)
      : destination(dest), size(sz), priority(prio), arrival_time(arr) {}
};

struct OrderRequest {
  int table_id;
  std::vector<std::string> items;
  int priority;
  int order_time;
  OrderRequest(int id, const std::vector<std::string>& itms, int prio, int time)
      : table_id(id), items(itms), priority(prio), order_time(time) {}
};

struct ProcessorState {
  int nextAvailableTime;
  int processorId;
  ProcessorState(int t, int id) : nextAvailableTime(t), processorId(id) {}
};

struct OrderInfo {
  int priority;
  int arrival;
  int id;
  OrderInfo(int p, int a, int i) : priority(p), arrival(a), id(i) {}
};

struct Packet {
  int priority;
  int arrival;
  int size;
  int id;
  Packet(int p, int a, int s, int i)
      : priority(p), arrival(a), size(s), id(i) {}
};

template <typename T>
class Queue {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* front_;
  Node* rear_;
  size_t size_;

 public:
  Queue() : front_(nullptr), rear_(nullptr), size_(0) {}
  ~Queue();

  void enqueue(const T& value);
  T dequeue();
  const T& peek() const;
  bool isEmpty() const { return size_ == 0; }
  size_t size() const { return size_; }
  void clear();

  std::vector<Result> processParallel(std::vector<std::pair<int, int>>& tasks,
                                      int processors);

  std::vector<Result> processOrders(std::vector<OrderRequest>& orders,
                                    int stations);
};

// Constant cooking times
const std::unordered_map<std::string, int> COOKING_TIMES = {
    {"steak", 20}, {"pasta", 15}, {"salad", 10}, {"soup", 12}, {"dessert", 8}};

#endif /* QUEUE_HPP */
