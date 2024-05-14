#include "rectangle.h"
#include "point.h"
#include "size.h"
#include <algorithm>

Rectangle::Rectangle(): p(), s(){};

Rectangle::Rectangle(Point p, Size s) {
    this->p = p;
    this->s = s;
}

Rectangle::Rectangle(const Rectangle& r) {
    p = r.get_p();
    s = r.get_s();
}

Point Rectangle::get_p() const {
    return p;
}

Size Rectangle::get_s() const {
    return s;
}

void Rectangle::set_p(const Point &p) {
    this->p = p;
}

void Rectangle::set_s(const Size &s) {
    this->s = s;
}

Rectangle Rectangle::operator+(const Point &p) {
    return Rectangle(Point(this->p.get_x() + p.get_x(), this->p.get_y() + p.get_y()), s);
}

Rectangle Rectangle::operator-(const Point &p) {
    return Rectangle(Point(this->p.get_x() - p.get_x(), this->p.get_y() - p.get_y()), s);
}

Rectangle Rectangle::operator&(const Rectangle &other) {
    Point topLeft(std::max(this->p.get_x(), other.get_p().get_x()), std::min(this->p.get_y(), other.get_p().get_y()));
    Point downRight(std::min(this->p.get_x() + this->s.get_width(), other.get_p().get_x() + other.get_s().get_width()), std::max(this->p.get_y() - this->s.get_height(), other.get_p().get_y() - other.get_s().get_height()));
    Size finalSize(downRight.get_x() - topLeft.get_x(), topLeft.get_y() - downRight.get_y());
    Rectangle ans(topLeft, finalSize);
    return ans;
}

Rectangle Rectangle::operator|(const Rectangle &r) {
    Point topLeft(std::min(this->p.get_x(), r.get_p().get_x()), std::max(this->p.get_y(), r.get_p().get_y()));
    Point downRight(std::max(this->p.get_x() + this->s.get_width(), r.get_p().get_x() + r.get_s().get_width()), std::min(this->p.get_y() - this->s.get_height(), r.get_p().get_y() - r.get_s().get_height()));
    Size finalSize(downRight.get_x() - topLeft.get_x(), topLeft.get_y() - downRight.get_y());
    Rectangle ans(topLeft, finalSize);
    return ans;
}

Rectangle& Rectangle::operator=(const Rectangle &r) {
    p = r.get_p();
    s = r.get_s();
    return *this;
}

Rectangle::~Rectangle() {

}