#ifndef QUAD_H
#define QUAD_H
#include "point.h"
#include <cmath>
#include <iostream>
#include <string>

class Quad {
  public:
    // Default constructor - Can leave points uninitialized but is not
    // valid until all 4 points are set
    Quad();
    // Initializing constructor - Sets all 4 points of the quadrilateral
    //  using the array of points provided in the argument.
    Quad(Point mypts[4]);
    // Change/set a point at the index given by idx
    void setPoint(int idx, Point p);
    // Returns the perimeter of the quadrilateral
    double perim() const;
    // Returns the area of the quadrilateral
    //  Multiple ways this can be computed
    //  https://byjus.com/maths/area-of-quadrilateral/
    double area() const;
    // Returns true if all 4 points have been set
    //  and all the interior angles add to 360,
    // Returns false, otherwise
    bool isValid() const;
    // Returns true if the quadrilateral is a square, false otherwise
    bool isSquare() const;
    // Returns true if the quadrilateral is a rectangle, false otherwise
    bool isRectangle() const;
    // Returns true if the quadrilateral is a rhombus, false otherwise
    bool isRhombus() const;
    // Returns true if the quadrilateral is a parallelogram, false otherwise
    bool isParallelogram() const;
    // returns a string version of the point vertices the quadrilateral
    //  in a format "(x0,y0) (x1,y1) (x2,y2) (x3,y3)" if the quadrilateral is
    //  valid of "invalid" if the quadrilateral is NOT valid
    std::string conv_to_string() const;

  private:
    // Computes the interior angle of three points given their indices as
    // arguments where the 2nd arg is the index of the vertex point of the angle
    double getInteriorAngle(int ext1, int vert, int ext2) const;

    // Data members
    // ============
    Point pts_[4]; // actual vertices of the quadrilateral

    // TODO: Add data members to ensure all 4 points are added
    bool init[4];
};

#endif