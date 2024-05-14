#include "point.h"

Point::Point(): x{0}, y{0} {}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point(const Point &p) {
    x = p.x;
    y = p.y;
}

int Point::get_x() const {
    return x;
}

int Point::get_y() const {
    return y;
}

void Point::set_x(int x) {
    this->x = x;
}

void Point::set_y(int y) {
    this->y = y;
}

Point& Point::operator=(const Point &p) {
    x = p.get_x();
    y = p.get_y();
    return *this;
}

Point::~Point() {

}