#include "quad.h"
#include <cmath>
#include <iostream>

// Global score helper functions for Quad member functions.
// Since we define at the top, and these are only meant to be used
// internally, we will forego the prototype

// Returns true if two doubles are within 0.001 of each other
//  Should be used for all equality and non-equality comparison
//  of doubles
bool same(double a, double b) {
    // TODO - complete this function based on the instructions
    //        above and description in the writeup
    if (std::abs(a - b) < .001)
        return true;
    return false;
}

// Complete - Returns the distance between two points
double dist(Point a, Point b) {
    return sqrt(pow(a.px - b.px, 2) + pow(a.py - b.py, 2));
}

// Quad member function definitions
// ================================
Quad::Quad() {
    // TODO - Add code to initialize the data member(s) you added
    //        to track which points have been initialized
    //        by user-specified values (and not default values).
    for (int i = 0; i < 4; i++) {
        pts_[i].px = 0; // give default values;
        pts_[i].py = 0; // give default values;
        init[i] = false;
    }
}
Quad::Quad(Point mypts[]) {
    // TODO - Add code to initialize the data member(s) you added
    //        to track which points have been initialized
    //        by user-specified values (and not default values).
    for (int i = 0; i < 4; i++) {
        pts_[i] = mypts[i];
        init[i] = true;
    }
}
// TODO - Define all other necessary member functions
void Quad::setPoint(int idx, Point p) {
    pts_[idx] = p;
    init[idx] = true;
}

bool Quad::isValid() const {
    for (int i = 0; i < 4; ++i) {
        if (init[i] == false)
            return false;
    }
    double angle1 = getInteriorAngle(1, 0, 3);
    double angle2 = getInteriorAngle(0, 1, 2);
    double angle3 = getInteriorAngle(1, 2, 3);
    double angle4 = getInteriorAngle(0, 3, 2);
    if (angle1 >= M_PI)
        return false;
    if (angle2 >= M_PI)
        return false;
    if (angle3 >= M_PI)
        return false;
    if (angle4 >= M_PI)
        return false;
    if (!same(angle1 + angle2 + angle3 + angle4, 2 * M_PI))
        return false;
    return true;
}

bool Quad::isSquare() const {
    if (!isValid())
        return false;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[0], pts_[3])))
        return false;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[1], pts_[2])))
        return false;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[2], pts_[3])))
        return false;
    if (!same(getInteriorAngle(1, 0, 3), M_PI / 2.0))
        return false;
    if (!same(getInteriorAngle(0, 1, 2), M_PI / 2.0))
        return false;
    if (!same(getInteriorAngle(1, 2, 3), M_PI / 2.0))
        return false;
    if (!same(getInteriorAngle(0, 3, 2), M_PI / 2.0))
        return false;
    return true;
}

bool Quad::isRectangle() const {
    if (!isValid())
        return false;
    if (isSquare())
        return true;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[2], pts_[3])))
        return false;
    if (!same(dist(pts_[0], pts_[3]), dist(pts_[1], pts_[2])))
        return false;
    if (!same(getInteriorAngle(1, 0, 3), M_PI / 2.0))
        return false;
    if (!same(getInteriorAngle(0, 1, 2), M_PI / 2.0))
        return false;
    if (!same(getInteriorAngle(1, 2, 3), M_PI / 2.0))
        return false;
    if (!same(getInteriorAngle(0, 3, 2), M_PI / 2.0))
        return false;
    return true;
}

bool Quad::isRhombus() const {
    if (!isValid())
        return false;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[0], pts_[3])))
        return false;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[1], pts_[2])))
        return false;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[2], pts_[3])))
        return false;
    if (!same(getInteriorAngle(1, 0, 3), getInteriorAngle(1, 2, 3)))
        return false;
    if (!same(getInteriorAngle(0, 1, 2), getInteriorAngle(2, 3, 0)))
        return false;
    return true;
}

bool Quad::isParallelogram() const {
    if (!isValid())
        return false;
    if (isRhombus())
        return true;
    if (!same(dist(pts_[0], pts_[1]), dist(pts_[2], pts_[3])))
        return false;
    if (!same(dist(pts_[0], pts_[3]), dist(pts_[1], pts_[2])))
        return false;
    if (!same(getInteriorAngle(1, 0, 3), getInteriorAngle(1, 2, 3)))
        return false;
    if (!same(getInteriorAngle(0, 1, 2), getInteriorAngle(2, 3, 0)))
        return false;
    return true;
}

double Quad::area() const {
    const double a = dist(pts_[0], pts_[1]);
    const double b = dist(pts_[0], pts_[3]);
    const double c = dist(pts_[1], pts_[2]);
    const double d = dist(pts_[3], pts_[2]);
    const double theta1 = getInteriorAngle(0, 1, 2);
    const double theta2 = getInteriorAngle(0, 3, 2);
    const double s = (a + b + c + d) / 2.0;
    const double theta = theta1 + theta2;
    return std::sqrt(
        (s - a)*(s - b)*(s - c)*(s - d)-a*b*c*d*std::pow(std::cos(theta / 2.0), 2)
    );
}

double Quad::perim() const {
    return dist(pts_[0], pts_[1]) + dist(pts_[0], pts_[3]) +
           dist(pts_[1], pts_[2]) + dist(pts_[3], pts_[2]);
}

std::string Quad::conv_to_string() const {
    std::string retval;
    if (isValid() == false) {
        return "invalid";
    }
    // TODO - Add code to produce and return the appropriate string
    //        representation of the Quad's points.
    for (int i = 0; i < 4; ++i) {
        retval += "(" + std::to_string(pts_[i].px) + "," +
                  std::to_string(pts_[i].py) + ")";
        if (i != 3)
            retval += " ";
    }
    return retval;
}

double Quad::getInteriorAngle(int ext1, int vert, int ext2) const {
    // TODO - Complete this function - remember the return type
    //        should be in units of radians
    const double ab = dist(pts_[ext1], pts_[vert]);
    const double bc = dist(pts_[ext2], pts_[vert]);
    const double ac = dist(pts_[ext2], pts_[ext1]);
    return std::acos((std::pow(ab, 2) + std::pow(bc, 2) - std::pow(ac, 2)) /
                     (2.0 * ab * bc));
}
