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
std::vector<Result> Queue<T>::processEmergencyRoom(
    std::vector<Patient>& patients, std::vector<Room>& rooms) {
  std::vector<Result> results;
  if (patients.empty() || rooms.empty()) return results;

  // Create priority queues for each severity level (1-4)
  std::vector<Queue<Patient>> severityQueues(5);  // 0 index unused

  // Distribute patients by severity
  for (auto& patient : patients) {
    severityQueues[patient.severity].enqueue(patient);
  }

  // Track room availability times (when they will be free next)
  std::vector<int> roomAvailableTime(rooms.size(), 0);

  // Process patients by severity (1 = most severe)
  for (int severity = 1; severity <= 4; severity++) {
    while (!severityQueues[severity].isEmpty()) {
      Patient current = severityQueues[severity].dequeue();

      // Find suitable room with earliest availability
      int selectedRoom = -1;
      int earliestTime = MAX_TIME;

      for (size_t i = 0; i < rooms.size(); i++) {
        // Check if room type matches requirement
        if (rooms[i].type == current.requiredRoomType) {
          if (roomAvailableTime[i] < earliestTime) {
            earliestTime = roomAvailableTime[i];
            selectedRoom = i;
          }
        }
      }

      if (selectedRoom != -1) {
        // Start time is the later of room's available time and patient's
        // arrival
        int startTime = (earliestTime > current.arrivalTime)
                            ? earliestTime
                            : current.arrivalTime;
        results.push_back(
            Result(current.id, startTime, rooms[selectedRoom].id));

        // Update room's next available time by adding current patient's
        // treatment duration
        roomAvailableTime[selectedRoom] =
            startTime + current.estimatedTreatmentTime;
      }
    }
  }

  return results;
}

// Replace the std::find check with a manual loop
bool hasExpertise(const Representative& rep, const std::string& expertise) {
  for (const auto& skill : rep.skills) {
    if (skill == expertise) {
      return true;
    }
  }
  return false;
}

template <typename T>
std::vector<Result> Queue<T>::processCustomerService(
    std::vector<ServiceRequest>& requests,
    std::vector<Representative>& representatives) {
  std::vector<Result> results;
  if (requests.empty() || representatives.empty()) return results;

  // Create priority queues for each priority level (1-3)
  std::vector<Queue<ServiceRequest>> priorityQueues(4);  // 0 index unused

  // Distribute requests by priority
  for (auto& request : requests) {
    priorityQueues[request.priority].enqueue(request);
  }

  // Track representative availability
  std::vector<int> repAvailableTime(representatives.size(), 0);

  // Process requests by priority
  for (int priority = 1; priority <= 3; priority++) {
    while (!priorityQueues[priority].isEmpty()) {
      ServiceRequest current = priorityQueues[priority].dequeue();

      // Find suitable representative with earliest availability
      int selectedRep = -1;
      int earliestTime = MAX_TIME;

      for (size_t i = 0; i < representatives.size(); i++) {
        // Check if representative has required expertise
        if (hasExpertise(representatives[i], current.expertise)) {
          if (repAvailableTime[i] < earliestTime) {
            earliestTime = repAvailableTime[i];
            selectedRep = i;
          }
        }
      }

      if (selectedRep != -1) {
        int startTime = (earliestTime > current.arrivalTime)
                            ? earliestTime
                            : current.arrivalTime;
        results.push_back(
            Result(current.id, startTime, representatives[selectedRep].id));
        repAvailableTime[selectedRep] = startTime + current.estimatedTime;
      }
    }
  }

  return results;
}

// Explicit template instantiations
template class Queue<int>;
template class Queue<double>;
template class Queue<char>;
template class Queue<std::string>;
template class Queue<Patient>;
template class Queue<ServiceRequest>;
