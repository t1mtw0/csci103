#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>

// Complete this header file below

class Course {
public:
    Course(std::string name, int credit);
    std::string getName();
    int getNumCredit();
    virtual std::string getFinalLetterGrade(double grade) = 0;
private:
    int credit;
    std::string name;
};

#endif
