//
//  main.cpp
//  render
//
//  Created by kross on 2020/11/24.
//

#include "tgaimage.h"
#include "iostream"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    for (float t = 0; t < 1; t += 0.01) {
        int x = x0 + (x1 - x0) * t;
        int y = y0 + (y1 - y0) * t;
        image.set(x, y, color);
    }
}

void line2(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    bool swaped = false;
    if (dy > dx) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        std::swap(dx, dy);
        swaped = true;
    }

    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);

    int x, y;

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    x = x0;
    y = y0;

    if (swaped) {
        image.set(y, x, color);
    } else {
        image.set(x, y, color);
    }

    while (x < x1) {
        x++;
        if (p < 0) {
            p += twoDy;
        } else {
            y++;
            p += twoDyMinusDx;
        }
        if (swaped) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

int main() {
    std::cout << "heelow" << std::endl;
    TGAImage image(1000, 1000, TGAImage::RGB);
    line2(10, 10, 500, 500, image, red);
    line2(10, 10, 50, 900, image, red);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
