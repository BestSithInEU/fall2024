#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/Color.hpp"
#include "../include/Queue.hpp"

void printHeader(const std::string& text) {
  std::cout << "\n" << Color::BOLD << Color::BLUE;
  std::cout << "+=" << std::string(48, '=') << "=+\n";
  std::cout << "| " << std::setw(48) << std::left << text << " |\n";
  std::cout << "+=" << std::string(48, '=') << "=+\n";
  std::cout << Color::RESET;
}

void testEmergencyRoom() {
  printHeader("Testing Emergency Room Processing");

  std::vector<Patient> patients = {
      Patient(1, 0, 120, 0, "ICU"),       // Critical patient, needs ICU
      Patient(2, 1, 60, 1, "Emergency"),  // Serious patient
      Patient(1, 2, 90, 2, "ICU"),        // Another critical patient
      Patient(3, 3, 45, 3, "General"),    // Moderate case
      Patient(4, 4, 30, 4, "General")     // Minor case
  };

  std::vector<Room> rooms = {Room("ICU", 1), Room("ICU", 2),
                             Room("Emergency", 3), Room("General", 4)};

  Queue<int> queue;
  auto results = queue.processEmergencyRoom(patients, rooms);

  std::cout << Color::CYAN << "Emergency Room Processing Results:\n"
            << Color::RESET;
  for (const auto& res : results) {
    std::cout << "Patient " << res.id << " assigned to Room " << res.resourceId
              << " starting at time " << res.time << "\n";
  }
}

void testCustomerService() {
  printHeader("Testing Customer Service Processing");

  std::vector<ServiceRequest> requests = {
      ServiceRequest(1, "Technical", 30, 0, 0),  // Urgent technical issue
      ServiceRequest(2, "Billing", 20, 1, 1),    // Normal billing query
      ServiceRequest(1, "Technical", 25, 2,
                     2),                      // Another urgent technical issue
      ServiceRequest(3, "General", 15, 3, 3)  // Low priority general query
  };

  std::vector<Representative> representatives = {
      Representative({"Technical", "General"}, 1),
      Representative({"Billing", "General"}, 2),
      Representative({"Technical", "Billing", "General"}, 3)};

  Queue<int> queue;
  auto results = queue.processCustomerService(requests, representatives);

  std::cout << Color::CYAN << "Customer Service Processing Results:\n"
            << Color::RESET;
  for (const auto& res : results) {
    std::cout << "Request " << res.id << " assigned to Representative "
              << res.resourceId << " starting at time " << res.time << "\n";
  }
}

int main() {
  printHeader("QUEUE OPERATIONS DEMONSTRATION");

  try {
    testEmergencyRoom();
    testCustomerService();
  } catch (const std::exception& e) {
    std::cout << Color::RED << "Error: " << e.what() << Color::RESET << "\n";
  }

  printHeader("DEMONSTRATION COMPLETED");
  return 0;
}
