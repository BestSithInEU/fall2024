#include "../include/Queue.hpp"

template <typename T>
Queue<T>::~Queue() {
  clear();
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
  Node* newNode = new Node(value);

  if (isEmpty()) {
    front_ = rear_ = newNode;
  } else {
    rear_->next = newNode;
    rear_ = newNode;
  }
  size_++;
}

template <typename T>
T Queue<T>::dequeue() {
  if (isEmpty()) {
    throw std::runtime_error("Cannot dequeue from empty queue");
  }

  Node* temp = front_;
  T value = front_->data;
  front_ = front_->next;
  delete temp;
  size_--;

  if (isEmpty()) {
    rear_ = nullptr;
  }

  return value;
}

template <typename T>
const T& Queue<T>::peek() const {
  if (isEmpty()) {
    throw std::runtime_error("Cannot peek empty queue");
  }
  return front_->data;
}

template <typename T>
void Queue<T>::clear() {
  while (!isEmpty()) {
    dequeue();
  }
}

template <typename T>
std::vector<Result> Queue<T>::processParallel(
    std::vector<std::pair<int, int>>& tasks, int processors) {
  std::vector<Result> result;
  if (tasks.empty() || processors <= 0) return result;

  // Create priority queues for each priority level
  std::vector<Queue<Task>> priorityQueues(4);  // Assuming priorities 1-3

  // Distribute tasks by priority
  for (size_t i = 0; i < tasks.size(); i++) {
    Task task(tasks[i].second, tasks[i].first, static_cast<int>(i));
    priorityQueues[task.priority].enqueue(task);
  }

  std::vector<ProcessorState> processorStates;
  for (int i = 1; i <= processors; i++) {
    processorStates.push_back(ProcessorState(0, i));
  }

  // Process tasks in priority order
  for (int priority = 1; priority <= 3; priority++) {
    while (!priorityQueues[priority].isEmpty()) {
      Task currentTask = priorityQueues[priority].dequeue();

      // Find earliest available processor
      int earliestTime = processorStates[0].nextAvailableTime;
      int selectedProcessor = processorStates[0].processorId;
      size_t selectedIdx = 0;

      for (size_t i = 1; i < processorStates.size(); i++) {
        if (processorStates[i].nextAvailableTime < earliestTime) {
          earliestTime = processorStates[i].nextAvailableTime;
          selectedProcessor = processorStates[i].processorId;
          selectedIdx = i;
        }
      }

      result.push_back(Result(currentTask.id, earliestTime, selectedProcessor));
      processorStates[selectedIdx].nextAvailableTime =
          earliestTime + currentTask.duration;
    }
  }

  return result;
}

template <typename T>
std::vector<Result> Queue<T>::processOrders(std::vector<OrderRequest>& orders,
                                            int stations) {
  std::vector<Result> result;
  if (orders.empty() || stations <= 0) return result;

  Queue<OrderInfo> orderQueue;
  for (size_t i = 0; i < orders.size(); i++) {
    auto& order = orders[i];
    orderQueue.enqueue(
        OrderInfo(order.priority, order.order_time, static_cast<int>(i)));
  }

  std::vector<ProcessorState> stationStates;
  for (int i = 1; i <= stations; i++) {
    stationStates.push_back(ProcessorState(0, i));
  }

  while (!orderQueue.isEmpty()) {
    OrderInfo currentOrder = orderQueue.dequeue();

    int totalTime = 0;
    for (const auto& item : orders[currentOrder.id].items) {
      totalTime += COOKING_TIMES.at(item);
    }

    int earliestTime = stationStates[0].nextAvailableTime;
    int selectedStation = stationStates[0].processorId;
    size_t selectedIdx = 0;

    for (size_t i = 1; i < stationStates.size(); i++) {
      if (stationStates[i].nextAvailableTime < earliestTime) {
        earliestTime = stationStates[i].nextAvailableTime;
        selectedStation = stationStates[i].processorId;
        selectedIdx = i;
      }
    }

    int startTime = earliestTime > currentOrder.arrival ? earliestTime
                                                        : currentOrder.arrival;
    result.push_back(
        Result(currentOrder.id, startTime + totalTime, selectedStation));
    stationStates[selectedIdx].nextAvailableTime = startTime + totalTime;
  }

  return result;
}

// Explicit template instantiations
template class Queue<int>;
template class Queue<double>;
template class Queue<char>;
template class Queue<std::string>;
template class Queue<std::pair<int, int>>;
template class Queue<PacketInfo>;
template class Queue<OrderRequest>;
