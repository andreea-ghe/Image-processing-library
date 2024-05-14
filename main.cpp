#include <iostream>
#include "image.h"
#include "ImageProcessing.h"
#include "drawing.h"
#include <fstream>

unsigned char ClipScale1(int val) {
    return val / 9;
}

unsigned char ClipScale2(int val) {
    return val / 16;
}

unsigned char ClipScale3(int val) {
    return (val + 4 * 255) / 8;
}

unsigned char ClipScale4(int val) {
    return val;
}

int main() {

    Image Img(512, 512);
    Img.load("../images/baboon.ascii.pgm");

    int ok = 1;
    Image result(512, 512);
    while (ok) {
        std::cout << "what operations do you want to perform?\n";
        int option;
        std::cout << "1. Adjust brightness and contrast\n";
        std::cout << "2. Correct overall brightness\n";
        std::cout << "3. Convolution\n";
        std::cout << "4. Draw a circle\n";
        std::cout << "5. Draw a line\n";
        std::cout << "6. Draw a rectangle\n";
        std::cout << "0. Exit\n";
        std::cin >> option;
        if (option == 1) {
            int alpha, beta;
            std::cout << "You must choose a linear function. Choose alpha:";
            std::cin >> alpha;
            std::cout << "Choose beta:";
            std::cin >> beta;
            Brightness_contrast bc(alpha, beta);
            bc.process(Img, result);
            Img = result;
            result.save("../images/photo.pgm");
        }
        else if (option == 2) {
            double gamma;
            std::cout << "You must choose a value for gamma:";
            std::cin >> gamma;
            Gamma_correction gc(gamma);
            gc.process(Img, result);
            Img = result;
            result.save("../images/photo.pgm");
        }
        else if (option == 3) {
            std::cout << "You must choose a kernel:\nPress 1 for mean blur kernel\nPress 2 for gaussian blur kernel\nPress 3 for horizontal sobel kernel\nPress 4 for vertical sobel kernel\n";
            int k;
            std::cin >> k;
            std::vector<std::vector<int>> kernel;
            if (k == 1) {
                char aux[3][3] = {1, 1, 1,
                                  1, 1, 1,
                                  1, 1, 1};
                for (int i = 0; i < 3; i ++) {
                    kernel.push_back(std::vector<int>(3));
                    for (int j = 0; j < 3; j++)
                        kernel.at(i).at(j) = aux[i][j];
                }
                Convolution c(kernel, ClipScale1);
                c.process(Img, result);
            }
            else if (k == 2) {
                char aux[3][3] = {1, 2, 1,
                                  2, 4, 2,
                                  1, 2, 1};

                for (int i = 0; i < 3; i ++) {
                    kernel.push_back(std::vector<int>(3));
                    for (int j = 0; j < 3; j++)
                        kernel.at(i).at(j) = aux[i][j];
                }
                Convolution c(kernel, ClipScale2);
                c.process(Img, result);
            }
            else if (k == 3) {
                char aux[3][3] = {1, 2, 1,
                                  0, 0, 0,
                                  -1, -2, -1};
                for (int i = 0; i < 3; i ++) {
                    kernel.push_back(std::vector<int>(3));
                    for (int j = 0; j < 3; j++)
                        kernel.at(i).at(j) = aux[i][j];
                }
                Convolution c(kernel, ClipScale3);
                c.process(Img, result);
            }
            else if (k == 4) {
                char aux[3][3] = {-1, 0, 1,
                                  -2, 0, 2,
                                  -1, 0, 1};
                for (int i = 0; i < 3; i ++) {
                    kernel.push_back(std::vector<int>(3));
                    for (int j = 0; j < 3; j++)
                        kernel.at(i).at(j) = aux[i][j];
                }
                Convolution c(kernel, ClipScale3);
                c.process(Img, result);
            }
            else {
                char aux[3][3] = {0, 0, 0,
                                  0, 1, 0,
                                  0, 0, 0};
                for (int i = 0; i < 3; i ++) {
                    kernel.push_back(std::vector<int>(3));
                    for (int j = 0; j < 3; j++)
                        kernel.at(i).at(j) = aux[i][j];
                }
                Convolution c(kernel, ClipScale4);
                c.process(Img, result);
            }

            Img = result;
            result.save("../images/photo.pgm");
        }
        else if (option == 4) {
            Point center;
            int x, y, radius, color;
            std::cout << "You must choose a center point. What's the x coordinate?\n";
            std::cin >> x;
            std::cout << "What's the y coordinate?\n";
            std::cin>> y;
            center.set_x(x);
            center.set_y(y);
            std::cout << "What's the radius of the circle?\n";
            std::cin>>radius;
            std::cout << "What color do you want it to be? (number between 0 and 255)\n";
            std::cin >> color;
            drawCircle(Img, center, radius, color);
            Img.save("../images/photo.pgm");
        }
        else if (option == 5) {
            Point p1, p2;
            int x1, y1, x2, y2, color;
            std::cout << "You must choose the first point. What's the x coordinate?\n";
            std::cin >> x1;
            std::cout << "What's the y coordinate?\n";
            std::cin >> y1;
            std::cout << "You must choose the second point. What's the x coordinate?\n";
            std::cin >> x2;
            std::cout << "What's the y coordinate?\n";
            std::cin >> y2;
            std::cout << "What color do you want it to be? (number between 0 and 255)\n";
            std::cin >> color;
            p1.set_x(x1);
            p1.set_y(y1);
            p2.set_x(x2);
            p2.set_y(y2);
            drawLine(Img, p1, p2, color);
            Img.save("../images/photo.pgm");
        }
        else if (option == 6) {
            std::cout << "How do you want to draw the rectangle? By point and size or by top left and bottom right corners?\n Press 1 for the first option and 2 for the second one\n";
            int r;
            std::cin >> r;
            if (r == 1) {
                Point p;
                Size s;
                int x, y, w, h, color;
                std::cout << "What's the x coordinate for the top left corner?\n";
                std::cin >> x;
                std::cout << "What's the y coordinate?\n";
                std::cin >> y;
                std::cout << "What's the width of the rectangle?\n";
                std::cin >> w;
                std::cout << "What's the height of the rectangle?\n";
                std::cin >> h;
                std::cout << "What color do you want it to be? (number between 0 and 255)\n";
                std::cin >> color;
                p.set_x(x);
                p.set_y(y);
                s.set_width(w);
                s.set_height(h);
                Rectangle rctg(p, s);
                drawRectangle(Img, rctg, color);
                Img.save("../images/photo.pgm");
            }
            else {
                Point p1, p2;
                int x1, y1, x2, y2, color;
                std::cout << "What's the x coordinate for the top left corner?\n";
                std::cin >> x1;
                std::cout << "What's the y coordinate?\n";
                std::cin >> y1;
                std::cout << "What's the x coordinate for the bottom right corner?\n";
                std::cin >> x2;
                std::cout << "What's the y coordinate?\n";
                std::cin >> y2;
                std::cout << "What color do you want it to be? (number between 0 and 255)\n";
                std::cin >> color;
                p1.set_x(x1);
                p1.set_y(y1);
                p2.set_x(x2);
                p2.set_y(y2);
                drawRectangle(Img, p1, p2, color);
                Img.save("../images/photo.pgm");
            }
        }
        else if (option == 0) {
            ok = 0;
            Img.save("../images/photo.pgm");
        }
    }

    return 0;
}
