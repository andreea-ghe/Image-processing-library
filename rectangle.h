#pragma once
#include "size.h"
#include "point.h"

class Rectangle {
private:
    Point p;
    Size s;
public:
    Rectangle();
    Rectangle(Point p, Size s);
    Rectangle(const Rectangle& r);
    Point get_p() const;
    Size get_s() const;
    void set_p(const Point& p);
    void set_s(const Size& s);
    Rectangle operator+(const Point& p);
    Rectangle operator-(const Point& p);
    Rectangle operator&(const Rectangle& r);
    Rectangle operator|(const Rectangle& r);
    Rectangle& operator=(const Rectangle& r);
    ~Rectangle();
};
