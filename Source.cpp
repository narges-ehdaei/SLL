#include<iostream>
#include"SINGLY_LINKED_LIST.h"
using namespace std;

int main() {
    // Creating a Singly Linked List of integers
    SLL<int> mySLL;

    // Adding elements to the list
    mySLL.addLast(10);
    mySLL.addLast(20);
    mySLL.addLast(30);

    // Displaying the elements using iterators
    Iterator<int> it = mySLL.begin();
    while (it != mySLL.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    // Adding elements at the beginning and end
    mySLL.addFirst(5);
    mySLL.addLast(40);

    // Displaying the updated elements
    for (int i = 0; i < mySLL.getSize(); ++i) {
        std::cout << mySLL.getInfo(i) << " ";
    }
    std::cout << std::endl;

    // Removing elements
    mySLL.remove(20);
    mySLL.removeLast();

    // Displaying the final list
    Iterator<int> it2 = mySLL.begin();
    while (it2 != mySLL.end()) {
        std::cout << *it2 << " ";
        ++it2;
    }
    std::cout << std::endl;

    return 0;
}
