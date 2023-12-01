#ifndef SCALECOURSE_H
#define SCALECOURSE_H

#include "course.h"
#include <iostream>
#include <string>
#include <vector>

// Complete this header file below

class ScaleCourse : public Course {
  public:
    ScaleCourse(std::string name, int credit, std::vector<double> scales);
    std::string getFinalLetterGrade(double grade);

  private:
    std::vector<double> scales;
};

#endif
