
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG png;       
  png.readFromFile("tests/pacman.png");

  FloodFilledImage image(png);

  BFS trav2(png, Point(100, 100), 0.5);
  MyColorPicker color2(30, HSLAPixel(100,150,200));
  image.addFloodFill( trav2, color2 );
  Animation animation = image.animate(1000);

  PNG last = animation.getFrame( animation.frameCount() - 1 );

  DFS trav1(last, Point(1, 1), 0.5);
  RainbowColorPicker color1(0.5);
  image.addFloodFill( trav1, color1 );
  animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
 
  return 0;
}
