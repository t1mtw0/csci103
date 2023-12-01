#include "passfailcourse.h"
#include <iostream>
#include <string>
#include <vector>

// You complete the cpp file below

PassFailCourse::PassFailCourse(std::string n, int c, double t)
    : Course(n, c), threshold{t} {}

std::string PassFailCourse::getFinalLetterGrade(double grade) {
    if (grade >= threshold)
        return "P";
    return "NP";
}
