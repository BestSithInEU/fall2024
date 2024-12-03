#include <iostream>

#include "../include/LinkedList.hpp"

template <typename T>
void printList(const LinkedList<T>& list, const std::string& message) {
  std::cout << message;
  list.print();
  std::cout << std::endl;
}

int main() {
  std::cout << "\n=== Linked List Operations Demo ===\n";

  // Basic operations tests
  LinkedList<int> list;
  for (int i = 1; i <= 9; ++i) {
    list.push_back(i);
  }
  printList(list, "Original list: ");

  list.reverseAlternateK(3);
  printList(list, "After reverseAlternateK(3): ");

  // Reset and test segregateEvenOdd
  list.clear();
  for (int i : {1, 2, 3, 4, 5, 6}) {
    list.push_back(i);
  }
  list.segregateEvenOdd();
  printList(list, "After segregateEvenOdd: ");

  // Reset and test foldList
  list.clear();
  for (int i : {1, 2, 3, 4, 5}) {
    list.push_back(i);
  }
  list.foldList();
  printList(list, "After foldList: ");

  // Test sortByFrequency
  std::cout << "\n=== Testing sortByFrequency ===\n";

  LinkedList<int> freqList1;
  for (int i : {2, 3, 2, 4, 5, 2, 4, 3}) {
    freqList1.push_back(i);
  }
  printList(freqList1, "Original list: ");
  freqList1.sortByFrequency();
  printList(freqList1, "After sortByFrequency: ");

  // Test case with equal frequencies
  LinkedList<int> freqList2;
  for (int i : {1, 2, 1, 3, 2, 3}) {
    freqList2.push_back(i);
  }
  printList(freqList2, "\nOriginal list with equal frequencies: ");
  freqList2.sortByFrequency();
  printList(freqList2, "After sortByFrequency: ");

  // Test case with single frequency
  LinkedList<int> freqList3;
  for (int i : {5, 2, 8, 1, 9}) {
    freqList3.push_back(i);
  }
  printList(freqList3, "\nOriginal list with single frequencies: ");
  freqList3.sortByFrequency();
  printList(freqList3, "After sortByFrequency: ");

  // Test sortByFrequency with more complex cases
  std::cout << "\n=== Testing sortByFrequency with Complex Cases ===\n";

  // Test case 1: High frequency numbers
  LinkedList<int> freqList4;
  for (int i : {2, 2, 2, 2, 3, 3, 3, 4, 4,
                5}) {  // 2(4 times), 3(3 times), 4(2 times), 5(1 time)
    freqList4.push_back(i);
  }
  printList(freqList4, "Original list (high frequency): ");
  freqList4.sortByFrequency();
  printList(freqList4, "After sortByFrequency: ");

  return 0;
}
