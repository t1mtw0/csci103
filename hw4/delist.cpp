#include "delist.h"
#include <iostream>

// Add your function implementations here
DEList::DEList() : head{NULL}, tail{NULL}, sz{0} {}

DEList::~DEList() {
    DEItem *curr = head;
    while (curr != NULL) {
        DEItem *temp = curr;
        curr = curr->next;
        delete temp;
    }
}

bool DEList::empty() const {
    if (sz == 0)
        return true;
    return false;
}

int DEList::size() const {
    return sz;
}

int DEList::front() const { 
    if (sz == 0) return -1;
    return head->val;
}

int DEList::back() const {
    if (sz == 0) return -1;
    return tail->val;
}

void DEList::push_front(int new_val) {
    sz++;
    DEItem *item = new DEItem;
    item->val = new_val;
    item->next = NULL;
    item->prev = NULL;
    if (sz == 1) {
        head = item;
        tail = item;
        return;
    }
    item->next = head;
    head->prev = item;
    head = item;
    if (sz == 1) tail = item;
}

void DEList::push_back(int new_val) {
    sz++;
    DEItem *item = new DEItem;
    item->val = new_val;
    item->next = NULL;
    item->prev = NULL;
    if (sz == 1) {
        head = item;
        tail = item;
        return;
    }
    tail->next = item;
    item->prev = tail;
    tail = item;
    if (sz == 1) head = item;
}

void DEList::pop_back() {
    if (sz == 0) return;
    sz--;
    DEItem *item = tail;
    if (sz == 0) {
        head = NULL;
        tail = NULL;
        delete item;
        return;
    }
    tail = tail->prev;
    tail->next->prev = NULL;
    tail->next = NULL;
    delete item;
}

void DEList::pop_front() {
    if (sz == 0) return;
    sz--;
    DEItem *item = head;
    if (sz == 0) {
        head = NULL;
        tail = NULL;
        delete item;
        return;
    }
    head = head->next;
    head->prev->next = NULL;
    head->prev = NULL;
    delete item;
}

std::string DEList::conv_to_string() const {
    std::string res = "";
    DEItem *curr = head;
    while (curr != NULL) {
        res += std::to_string(curr->val);
        if (curr->next != NULL)
            res += " ";
        curr = curr->next;
    }
    return res;
}