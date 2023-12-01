#include "student.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

Student::Student(std::string name) {
    name_ = name;
    courses_ = {};
    grades_ = {};
}

void Student::setMajor(std::string major) {
    major_ = major;
}

// Add course to the courses_ vector
// Add course_grade to the grades_ vector
void Student::addCourse(Course *course, double course_grade) {
    courses_.push_back(course);
    grades_.push_back(course_grade);
}

// Compute the overall GPA
double Student::getTotalGPA() const {
    double total = 0;
    int scale = 0;
    for (unsigned int i = 0; i < courses_.size(); ++i) {
        Course *c = courses_[i];
        std::string g = c->getFinalLetterGrade(grades_[i]);
        if (g == "P" || g == "NP") continue;
        if (g == "A") {
            total += 4 * c->getNumCredit();
        } else if (g == "B") {
            total += 3 * c->getNumCredit();
        } else if (g == "C") {
            total += 2 * c->getNumCredit();
        } else if (g == "D") {
            total += 1 * c->getNumCredit();
        }
        scale += c->getNumCredit();
    }
    return (double)total / (double)scale;
}

// Get the total course credits.
int Student::getSemesterCourseCredit() const {
    int total = 0;
    for (unsigned int i = 0; i < courses_.size(); ++i) {
        Course *c = courses_[i];
        std::string g = c->getFinalLetterGrade(grades_[i]);
        if (g == "NP") continue;
        total += c->getNumCredit();
    }
    return total;
}

//***********************
// This function is done.
// do Not change anything
//***********************
void Student::printReport() const {
    std::cout << "Name: " << name_ << std::endl;
    std::cout << "Major: " << major_ << std::endl;
    std::cout << "Courses Taken: " << std::endl;
    std::cout << '|' << std::setw(10) << "Course";
    std::cout << '|' << std::setw(10) << "Credit";
    std::cout << '|' << std::setw(10) << "RawGrade";
    std::cout << '|' << std::setw(12) << "LetterGrade";
    std::cout << std::endl;
    std::cout << '|' << std::setw(10) << "----------";
    std::cout << '|' << std::setw(10) << "----------";
    std::cout << '|' << std::setw(10) << "----------";
    std::cout << '|' << std::setw(12) << "------------";
    std::cout << std::endl;
    for (size_t i = 0; i < courses_.size(); i++) {
        std::cout << '|' << std::setw(10) << courses_[i]->getName();
        std::cout << '|' << std::setw(10) << courses_[i]->getNumCredit();
        std::cout << '|' << std::setw(10) << grades_[i];
        std::cout << '|' << std::setw(12)
                  << courses_[i]->getFinalLetterGrade(grades_[i]);
        std::cout << std::endl;
    }
    std::cout << '|' << std::setw(10) << "----------";
    std::cout << '|' << std::setw(10) << "----------";
    std::cout << '|' << std::setw(10) << "----------";
    std::cout << '|' << std::setw(12) << "------------";
    std::cout << std::endl;
    std::cout << "Total Credits: " << getSemesterCourseCredit() << std::endl;
    std::cout << "Overall GPA: " << std::setprecision(2) << std::fixed
              << getTotalGPA() << std::endl;
}
