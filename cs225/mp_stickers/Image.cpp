/**
 * @file Image.cpp
 * Implementation of the Truck class.
 */

#include "Image.h"
#include <cmath>
#include <iostream>

using cs225::PNG;
using cs225::HSLAPixel;

Image::Image(unsigned int width, unsigned int height)
    : PNG(width, height) {}

Image::Image(PNG const & other)
    : PNG(other) {}

Image::Image() 
    : PNG() {}

Image:: ~Image() {}

void Image::lighten() {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if ((currPixel.l + .1) <= 1) {
                currPixel.l += .1;
            } else {
                currPixel.l = 1.0;
            }
        }
    }
}
        
void Image::lighten(double amount) {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if ((currPixel.l + amount) <= 1) {
                currPixel.l += amount;
            } else {
                currPixel.l = 1.0;
            }
        }
    }
}

void Image::darken() {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if (0 <= (currPixel.l - .1)) {
                currPixel.l -= .1;
            } else {
                currPixel.l = 0.0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if (0 <= (currPixel.l - amount)) {
                currPixel.l -= amount;
            } else {
                currPixel.l = 0.0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if ((currPixel.s + .1) <= 1) {
                currPixel.s += .1;
            } else {
                currPixel.s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if ((currPixel.s + amount) <= 1) {
                currPixel.s += amount;
            } else {
                currPixel.s = 1.0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if (0 <= (currPixel.s - .1)) {
                currPixel.s -= .1;
            } else {
                currPixel.s = 0.0;
            }
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if (0 <= (currPixel.s - amount)) {
                currPixel.s -= amount;
            } else {
                currPixel.s = 0.0;
            }
        }
    }
}

void Image::grayscale() {

}

void Image::rotateColor(double degrees) {
    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            HSLAPixel& currPixel = getPixel(x,y);
            if ( (currPixel.h + degrees) > 360 ) {
                currPixel.h = currPixel.h + degrees - 360;
            } else if ( (currPixel.h + degrees) < 0 ) {
                currPixel.h = 360 + currPixel.h + degrees;
            } else {
                currPixel.h = currPixel.h + degrees;
            }
        }
    }
}

void Image::illinify() {

}

void Image::scale(double factor) {
    Image newImage = Image( width() * factor, height() * factor);
    for (unsigned y = 0; y < newImage.height(); y++) {
        for (unsigned x = 0; x < newImage.width() ; x++) {
            newImage.getPixel(x,y) = getPixel( trunc(x / factor), trunc(y / factor) );
        }
    }

    resize( width() * factor, height() * factor);

    for (unsigned y = 0; y < this->height(); y++) {
        for (unsigned x = 0; x < this->width() ; x++) {
            getPixel(x,y) = newImage.getPixel(x,y);
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    Image newImage = Image( width() * w, height() * h);

    for (unsigned y = 0; y < newImage.height(); y++) {
        for (unsigned x = 0; x < newImage.width() ; x++) {
            newImage.getPixel(x,y) = getPixel( trunc(x / w), trunc(y / h) );
        }
    }

    resize( width() * w, height() * h);

    for (unsigned y = 0; y < height(); y++) {
        for (unsigned x = 0; x < width() ; x++) {
            getPixel(x,y) = newImage.getPixel(x,y);
        }
    }
}