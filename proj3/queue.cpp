/*
queue.cpp
*/

#include "queue.h"

// Constructor. maxlen must be as large as the total number
//  of Locations that will ever be entered into this Queue.
Queue::Queue(int maxlen) {
    head = 0;
    tail = 0;
    // *** You complete **** CHECKPOINT 3
    // need storage!!
    contents = new Location[maxlen];
}

// Destructor. releases resources. C++ will call it automatically.
Queue::~Queue() {
    // *** You complete **** CHECKPOINT 3
    delete[] contents;
}

// Insert a new Location at the end/back of our list
void Queue::add_to_back(Location loc) {
    contents[tail++] = loc;
    // *** You complete **** CHECKPOINT 3
}

// Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {
    return contents[head++];
    // *** You complete **** CHECKPOINT 3
}

// Is this Queue empty? (did we extract everything added?)
// This is complete, you don't need to change it.
bool Queue::is_empty() { return head == tail; }
