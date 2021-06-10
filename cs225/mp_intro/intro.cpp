#include <iostream>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

#include <cstdlib>
#include <cmath>
//using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG* original = new cs225::PNG();
  original->readFromFile(inputFile);
  
  unsigned width = original->width();
  unsigned height = original->height();

  cs225::PNG* output = new cs225::PNG(width, height);

  for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {   
        (*output).getPixel(width-1-x, height-1-y) = (*original).getPixel(x,y);
      }
  }

  // Save the output file
  output->writeToFile(outputFile);

  // Clean up memory

  //delete myPixel;
  delete output;
  delete original;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);

  // TODO: Part 3

  int r1 = rand() % 360;
  int g1 = rand() % 360;
  int b1 = rand() % 360;
  int x1 = rand() % width;
  int y1 = rand() % height;

  int r2 = rand() % 360;
  int g2 = rand() % 360;
  int b2 = rand() % 360;
  int x2 = rand() % width;
  int y2 = rand() % height;

  int r3 = rand() % 360;
  int g3 = rand() % 360;
  int b3 = rand() % 360;
  int x3 = rand() % width;
  int y3 = rand() % height;

  for (unsigned y = 0; y < height; y++) {
    for (unsigned x = 0; x < width; x++) {   

      int d1 = sqrt( (x-x1)*(x-x1) + (y-y1)*(y-y1) );
      int d2 = sqrt( (x-x2)*(x-x2) + (y-y2)*(y-y2) );
      int d3 = sqrt( (x-x3)*(x-x3) + (y-y3)*(y-y3) );

      int r = ( r1/(1+d1/30) + r2/(1+d2/40) + r3/(1+d3/70) )/3;
      int g = ( g1/(1+d1/20) + g2/(1+d2/30) + g3/(1+d3/50) )/3;
      int b = ( b1/(1+d1/80) + b2/(1+d2/20) + b3/(1+d3/60) )/3;
      
      cs225::HSLAPixel p(r, g, b);
      png.getPixel(x,y) = p;

    }
  }
  return png;
}
