#include <cmath>
#include <iostream>

#include "bmplib.h"

// global variable. bad style but ok for this assignment
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
    for (int i = top; i < height + top; ++i) {
        if (left < 0 || left >= SIZE)
            break;
        if (i < 0 || i >= SIZE)
            continue;
        image[i][left] = 0;
    }
    for (int i = top; i < height + top; ++i) {
        if (left + width - 1 < 0 || left + width - 1 >= SIZE)
            break;
        if (i < 0 || i >= SIZE)
            continue;
        image[i][left + width - 1] = 0;
    }
    for (int j = left; j < width + left; ++j) {
        if (top < 0 || top >= SIZE)
            break;
        if (j < 0 || j >= SIZE)
            continue;
        image[top][j] = 0;
    }
    for (int j = left; j < width + left; ++j) {
        if (top + height - 1 < 0 || top + height - 1 >= SIZE)
            break;
        if (j < 0 || j >= SIZE)
            continue;
        image[top + height - 1][j] = 0;
    }
}

// Fill in this function:
void draw_ellipse(int cr, int cc, int height, int width) {
    for (double a = 0.0; a < 2 * M_PI; a += 0.01) {
        double x = (width / 2.0) * std::cos(a);
        double y = (height / 2.0) * std::sin(a);
        x += cc;
        y += cr;
        if ((int)x < 0 || (int)x >= SIZE || (int)y < 0 || (int)y >= SIZE) continue;
        std::cout << (int)x << " " << (int)y << "\n";
        image[(int)y][(int)x] = 0;
    }
}

// Complete
void print_menu() {
    std::cout << "To draw a rectangle, enter: 0 top left height width\n";
    std::cout << "To draw an ellipse, enter: 1 cy cx height width\n";
    std::cout << "To save your drawing as 'output.bmp' and quit, enter: 2\n";
}

int main() {
    // initialization
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }
    int cmd;
    int height, width;
    int top, left;
    int cr, cc;
    // Main program loop here
    while (true) {
        print_menu();
        std::cin >> cmd;
        if (cmd == 2)
            break;
        if (cmd == 0) {
            std::cin >> top >> left >> height >> width;
            draw_rectangle(top, left, height, width);
        } else if (cmd == 1) {
            std::cin >> cr >> cc >> height >> width;
            draw_ellipse(cr, cc, height, width);
        }
    }
    // Write the resulting image to the .bmp file
    writeGSBMP("output.bmp", image);

    return 0;
}
