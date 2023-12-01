#ifndef PASSFAILCOURSE_H
#define PASSFAILCOURSE_H

#include "course.h"
#include <iostream>
#include <string>
#include <vector>

// Complete this header file below

class PassFailCourse : public Course {
  public:
    PassFailCourse(std::string name, int credit, double threshold);
    std::string getFinalLetterGrade(double grade);

  private:
    double threshold;
};

#endif