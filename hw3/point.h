#ifndef POINT_H
#define POINT_H
struct Point {
    // Default construct point to (0,0)
    Point() {
        px = 0;
        py = 0;
    }
    // Initializing constructor to user defined coordinates
    Point(double x, double y) {
        px = x;
        py = y;
    }
    double px;
    double py;
};

#endif