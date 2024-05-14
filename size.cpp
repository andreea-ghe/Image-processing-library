#include "size.h"

Size::Size(): width{0}, height{0}{}

Size::Size(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

Size::Size(const Size& s) {
    width = s.width;
    height = s.height;
}

bool Size::operator==(const Size &s) const {
    return (width == s.width && height == s.height);
}

bool Size::operator<(const Size &s) const {
    return (width*height < s.width*s.height);
}

bool Size::operator<=(const Size &s) const {
    return (width*height <= s.width*s.height);
}

bool Size::operator>(const Size &s) const {
    return (width*height > s.width*s.height);
}

bool Size::operator>=(const Size &s) const {
    return (width*height >= s.width*s.height);
}

unsigned int Size::get_width() const {
    return width;
}

unsigned int Size::get_height() const {
    return height;
}

void Size::set_width(unsigned int width) {
    this->width = width;
}

void Size::set_height(unsigned int height) {
    this->height = height;
}

Size& Size::operator=(const Size &s) {
    width = s.get_width();
    height = s.get_height();
    return *this;
}

Size::~Size() {

}