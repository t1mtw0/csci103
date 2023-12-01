#include "delist.h"
#include <iostream>

int main() {
    DEList list;
    list.push_back(1);
    std::cout << "Added 1 to the list and now front is " << list.front() << "\n";
    list.pop_front();
    std::cout << "Removed item\n";
    list.push_front(2);
    std::cout << "Added 2 to the list and now back is " << list.back() << "\n";
    list.pop_back();
    std::cout << "Removed item\n";

    for (int i = 0; i < 5; i++) {
        list.push_back(10 + i);
        list.push_front(20 + i);
    }
    std::cout << "List contents: " << list.conv_to_string() << "\n";
    std::cout << "List size after adding 10 elements is " << list.size() << "\n";
    while (!list.empty()) {
        std::cout << "Popping front item = " << list.front() << "\n";
        list.pop_front();
    }
    std::cout << "Trying to pop an item that doesn't exist\n";
    list.pop_front();

    std::cout << "Looking at values from front() and back() of empty list: \n";
    std::cout << list.front() << " " << list.back() << "\n";
    std::cout << "Repopulating list\n";
    for (int i = 0; i < 5; i++) {
        list.push_back(10 + i);
        list.push_front(20 + i);
    }
    while (!list.empty()) {
        std::cout << "Popping back item = " << list.back() << "\n";
        list.pop_back();
    }
    std::cout << "Trying to pop an item that doesn't exist\n";
    list.pop_back();

    list.push_back(100);
    list.push_front(101);
    std::cout << "Goodbye!\n";
    return 0;
}
