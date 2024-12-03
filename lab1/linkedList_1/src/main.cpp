#include <iostream>

#include "../include/LinkedList.hpp"

int main() {
  LinkedList<int> list;

  // Test push_front, push_back, and print
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_front(0);
  std::cout << "List after push_front and push_back: ";
  list.print();

  // Test reverseInGroups
  list.reverseInGroups(2);
  std::cout << "List after reverseInGroups(2): ";
  list.print();

  // Test findKthFromEnd
  try {
    int k = 2;
    int kthFromEnd = list.findKthFromEnd(k);
    std::cout << "Element " << k << " from the end is: " << kthFromEnd
              << std::endl;
  } catch (const std::out_of_range& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  // Test detectAndRemoveLoop
  list.push_back(2);  // Create a loop for testing
  bool hasLoop = list.detectAndRemoveLoop();
  std::cout << "List has loop: " << std::boolalpha << hasLoop << std::endl;
  std::cout << "List after detectAndRemoveLoop: ";
  list.print();

  // Test detectAndRemoveLoop with a cycle
  list.clear();
  for (int i = 1; i <= 5; i++) {
    list.push_back(i);
  }
  std::cout << "List after push_back: ";
  list.print();
  list.createCycle(2);  // Create a cycle starting at index 2 (value 3)

  // list.print();  // COMMENT THIS LINE, OUTPUT:
  // 1 -> 2 -> 3 -> 4 -> 5 -> 3 -> 4 -> 5 -> 3 -> 4 -> 5

  hasLoop = list.detectAndRemoveLoop();
  std::cout << "List has loop (with cycle): " << std::boolalpha << hasLoop
            << std::endl;
  std::cout << "List after detectAndRemoveLoop (with cycle): ";
  list.print();

  return 0;
}
