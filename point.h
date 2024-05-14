#pragma once

class Point {
private:
    int x, y;
public:
    Point();
    Point(int x, int y);
    Point(const Point& p);
    int get_x() const;
    int get_y() const;
    void set_x(int x);
    void set_y(int y);
    Point& operator=(const Point& p);
    ~Point();
};
