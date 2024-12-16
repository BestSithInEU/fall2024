#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations of all structs
struct Result;
struct Patient;
struct ServiceRequest;
struct Representative;
struct Room;

struct Result {
  int id;
  int time;
  int resourceId;
  Result(int i, int t, int r) : id(i), time(t), resourceId(r) {}
};

struct Patient {
  int severity;  // 1 (Critical) to 4 (Minor)
  int arrivalTime;
  int estimatedTreatmentTime;
  int id;
  std::string requiredRoomType;  // "ICU", "Emergency", "General"

  Patient(int sev, int arr, int treat, int i, const std::string& room)
      : severity(sev),
        arrivalTime(arr),
        estimatedTreatmentTime(treat),
        id(i),
        requiredRoomType(room) {}
};

struct ServiceRequest {
  int priority;  // 1 (Urgent) to 3 (Normal)
  std::string
      expertise;      // Required expertise: "Technical", "Billing", "General"
  int estimatedTime;  // Estimated handling time in minutes
  int arrivalTime;
  int id;

  ServiceRequest(int p, const std::string& exp, int est, int arr, int i)
      : priority(p),
        expertise(exp),
        estimatedTime(est),
        arrivalTime(arr),
        id(i) {}
};

struct Representative {
  std::vector<std::string> skills;
  int id;
  Representative(const std::vector<std::string>& s, int i) : skills(s), id(i) {}
};

struct Room {
  std::string type;
  int id;
  Room(const std::string& t, int i) : type(t), id(i) {}
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

  /**
   * Process hospital emergency room patients considering severity levels and
   * room types
   *
   * @param patients Vector of Patient objects with severity and treatment
   * details
   * @param rooms Vector of available treatment rooms with their types
   * @return Vector of Results containing {patient_id, treatment_start_time,
   * room_id}
   */
  std::vector<Result> processEmergencyRoom(std::vector<Patient>& patients,
                                           std::vector<Room>& rooms);

  /**
   * Process customer service requests matching them with representatives
   *
   * @param requests Vector of ServiceRequest objects
   * @param representatives Vector of available customer service representatives
   * @return Vector of Results containing {request_id, handling_start_time,
   * representative_id}
   */
  std::vector<Result> processCustomerService(
      std::vector<ServiceRequest>& requests,
      std::vector<Representative>& representatives);
};

const std::unordered_map<std::string, int> EXPERTISE_WEIGHTS = {
    {"Technical", 3}, {"Billing", 2}, {"General", 1}};

const std::unordered_map<std::string, int> ROOM_PRIORITIES = {
    {"ICU", 1}, {"Emergency", 2}, {"General", 3}};

const int MAX_TIME = 1000000;  // Large value to represent infinity

#endif /* QUEUE_HPP */
