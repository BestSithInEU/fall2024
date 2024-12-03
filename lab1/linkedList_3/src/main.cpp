#include <iostream>

#include "../include/LinkedList.hpp"

int main() {
  std::cout << "\n=== Linked List Operations Demo ===\n";

  // Create and populate a list
  LinkedList<int> list;
  for (int i = 1; i <= 8; ++i) {
    list.push_back(i);
  }

  // Demonstrate reverseInGroups
  std::cout << "\n1. Reverse in Groups Operation (k=3)\n";
  std::cout << "Before: ";
  list.print();
  list.reverseInGroups(3);
  std::cout << "After:  ";
  list.print();

  // Demonstrate swapPairs
  LinkedList<int> list2;
  for (int i = 1; i <= 6; ++i) {
    list2.push_back(i);
  }
  std::cout << "\n2. Swap Pairs Operation\n";
  std::cout << "Before: ";
  list2.print();
  list2.swapPairs();
  std::cout << "After:  ";
  list2.print();

  // Demonstrate mergeSorted
  std::cout << "\n3. Merge Sorted Lists Operation\n";
  LinkedList<int> list3, list4;
  for (int i = 1; i <= 7; i += 2) list3.push_back(i);  // 1,3,5,7
  for (int i = 2; i <= 8; i += 2) list4.push_back(i);  // 2,4,6,8
  std::cout << "List 1: ";
  list3.print();
  std::cout << "List 2: ";
  list4.print();
  list3.mergeSorted(list4);
  std::cout << "Merged:  ";
  list3.print();

  // Demonstrate partitionList
  std::cout << "\n4. Partition List Operation (x=5)\n";
  LinkedList<int> list5;
  int values[] = {3, 7, 8, 5, 2, 1};
  for (int val : values) {
    list5.push_back(val);
  }
  std::cout << "Before: ";
  list5.print();
  list5.partitionList(5);
  std::cout << "After:  ";
  list5.print();

  return 0;
}
