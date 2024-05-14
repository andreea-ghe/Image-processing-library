#include "image.h"
#include "point.h"
#include "rectangle.h"

void drawCircle(Image& img, Point center, int radius, unsigned char color);
void drawLine(Image &img, Point p1, Point p2, unsigned char color);
void drawRectangle(Image &img, Rectangle r, unsigned char color);
void drawRectangle(Image &img, Point tl, Point br, unsigned char color);