#ifndef DELIST_H
#define DELIST_H

#include <string>

struct DEItem {
    int val;
    DEItem *prev;
    DEItem *next;
};

class DEList {
  public:
    // Constructs an empty Double-Ended List
    DEList();
    // Destructor to clean-up memory of current list
    ~DEList();
    // returns a Boolean 'true' if the list is empty
    bool empty() const;
    // returns number of items in the list
    int size() const;
    // returns front item or -1 if empty list
    int front() const;
    // returns back item or -1 if empty list
    int back() const;
    // Adds a new integer to the front of the list
    void push_front(int new_val);
    // Adds a new integer to the back of the list
    void push_back(int new_val);
    // Removes the front item of the list (if it exists)
    void pop_front();
    // Removes the back item of the list (if it exists)
    void pop_back();
    // Converts the contents of the list to a string with spaces between
    // each element an NO trailing newline (and no space before the
    // first element or after the last element)
    std::string conv_to_string() const;

  private:
    // ADD your data members here:
    DEItem *head;
    DEItem *tail;
    int sz;
};

#endif
