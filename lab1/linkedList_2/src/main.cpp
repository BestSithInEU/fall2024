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

  // Test rotateRight
  list.rotateRight(2);
  std::cout << "List after rotateRight(2): ";
  list.print();

  // Test isPalindrome
  LinkedList<int> palindromeList;
  palindromeList.push_back(1);
  palindromeList.push_back(2);
  palindromeList.push_back(3);
  palindromeList.push_back(2);
  palindromeList.push_back(1);
  std::cout << "Is palindromeList a palindrome? " << std::boolalpha
            << palindromeList.isPalindrome() << std::endl;

  // Test removeDuplicates
  LinkedList<int> duplicatesList;
  duplicatesList.push_back(1);
  duplicatesList.push_back(2);
  duplicatesList.push_back(2);
  duplicatesList.push_back(3);
  duplicatesList.push_back(3);
  duplicatesList.push_back(4);
  std::cout << "List before removeDuplicates: ";
  duplicatesList.print();
  duplicatesList.removeDuplicates();
  std::cout << "List after removeDuplicates: ";
  duplicatesList.print();

  // Test sort
  LinkedList<int> unsortedList;
  unsortedList.push_back(5);
  unsortedList.push_back(2);
  unsortedList.push_back(7);
  unsortedList.push_back(1);
  unsortedList.push_back(9);
  std::cout << "List before sort: ";
  unsortedList.print();
  unsortedList.sort(true);
  std::cout << "List after sort (ascending): ";
  unsortedList.print();
  unsortedList.sort(false);
  std::cout << "List after sort (descending): ";
  unsortedList.print();

  return 0;
}
