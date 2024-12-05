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

void testProcessParallel() {
  printHeader("Testing Process Parallel");

  std::vector<std::pair<int, int>> tasks = {{4, 1},  // {duration, priority}
                                            {2, 2},
                                            {3, 1},
                                            {1, 3}};

  Queue<int> queue;
  auto result = queue.processParallel(tasks, 2);

  std::cout << "Task scheduling results:\n";
  for (const auto& res : result) {
    std::cout << "Task " << res.id << " starts at " << res.time
              << " on processor " << res.resourceId << "\n";
  }
}

void testProcessOrders() {
  printHeader("Testing Process Orders");

  std::vector<OrderRequest> orders = {
      OrderRequest(1, {"steak", "salad"}, 2, 0),
      OrderRequest(2, {"pasta"}, 1, 1),
      OrderRequest(3, {"soup", "dessert"}, 3, 2)};

  Queue<int> queue;
  auto result = queue.processOrders(orders, 2);

  std::cout << "Order processing results:\n";
  for (const auto& res : result) {
    std::cout << "Order " << res.id << " completed at " << res.time
              << " on station " << res.resourceId << "\n";
  }
}

int main() {
  printHeader("QUEUE OPERATIONS DEMONSTRATION");

  try {
    testProcessParallel();
    testProcessOrders();
  } catch (const std::exception& e) {
    std::cout << Color::RED << "Error: " << e.what() << Color::RESET << "\n";
  }

  printHeader("DEMONSTRATION COMPLETED");
  return 0;
}
