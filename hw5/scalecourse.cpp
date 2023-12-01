#include <iostream>
#include <string>
#include <vector>
#include "scalecourse.h"

//You complete the cpp file below

ScaleCourse::ScaleCourse(std::string n, int c, std::vector<double> s) : Course(n, c), scales{s} {};

std::string ScaleCourse::getFinalLetterGrade(double grade) {
    if (grade >= scales[0]) {
        return "A";
    } else if (grade >= scales[1]) {
        return "B";
    } else if (grade >= scales[2]) {
        return "C";
    } else if (grade >= scales[3]) {
        return "D";
    } else {
        return "F";
    }
}
