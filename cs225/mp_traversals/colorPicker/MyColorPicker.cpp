#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(double number, HSLAPixel pixel) : n(number), pixel(pixel) { 

}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel newPixel(pixel.h, pixel.s, pixel.l);
  newPixel.h = newPixel.h * (n+x+y) / (n+x+y+100);
  newPixel.s = newPixel.s * n / (n+1);

  return newPixel;
}
