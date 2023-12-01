#include "course.h"
#include <iostream>
#include <string>
#include <vector>

// You complete the cpp file below

Course::Course(std::string n, int c) {
    credit = c;
    name = n;
}

std::string Course::getName() { return name; }

int Course::getNumCredit() { return credit; }
