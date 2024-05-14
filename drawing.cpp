#include "image.h"
#include "point.h"
#include "rectangle.h"
#include "drawing.h"

void drawCircle(Image& img, Point center, int radius, unsigned char color) {
    for (int x = 0; x < img.width(); x ++)
        for (int y = 0; y < img.height(); y ++)
            if ((x - center.get_x()) * (x - center.get_x()) + (y - center.get_y()) * (y - center.get_y()) <= radius * radius)
                img.at(x, y) = color;
}

void drawLine(Image &img, Point p1, Point p2, unsigned char color) {
    int x1 = p1.get_x(), y1 = p1.get_y();
    int x2 = p2.get_x(), y2 = p2.get_y();
    if (x1 <= x2) {
        if (y1 <= y2)
            for (int x = x1, y = y1; x <= x2, y <= y2; x ++, y ++)
                img.at(x, y) = color;
        else
            for (int x = x1, y = y2; x <= x2, y <= y1; x ++, y ++)
                img.at(x, y) = color;
    }
    else {
        if (y1 <= y2)
            for (int x = x2, y = y1; x <= x1, y <= y2; x ++, y ++)
                img.at(x, y) = color;
        else
            for (int x = x2, y = y2; x <= x1, y <= y1; x ++, y ++)
                img.at(x, y) = color;
    }

}

void drawRectangle(Image &img, Rectangle r, unsigned char color) {
    for (int x = r.get_p().get_x(); x < r.get_p().get_x() + r.get_s().get_width(); x ++)
        for (int y = r.get_p().get_y(); y < r.get_p().get_y() + r.get_s().get_height(); y ++)
            img.at(x, y) = color;
}

void drawRectangle(Image &img, Point tl, Point br, unsigned char color) {
    for (int x = tl.get_x(); x < br.get_x(); x ++)
        for (int y = tl.get_y(); y < br.get_y(); y ++)
            img.at(x, y) = color;
}