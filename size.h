#pragma once

class Size {
private:
    unsigned int width, height;
public:
    Size();
    Size(unsigned int width, unsigned int height);
    Size(const Size& s);
    bool operator==(const Size& s) const;
    bool operator<(const Size& s) const;
    bool operator<=(const Size& s) const;
    bool operator>(const Size& s) const;
    bool operator>=(const Size& s) const;
    unsigned int get_width() const;
    unsigned int get_height() const;
    void set_width(unsigned int width);
    void set_height(unsigned int height);
    Size& operator=(const Size& s);
    ~Size();
};
