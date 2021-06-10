#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(PNG png_) {
  /** @todo [Part 2] */
  finalFrame = new PNG(png_);
  // finalFrame = PNG(png_.width(), png_.height());
  // for (unsigned i = 0; i < png_.width(); i++) {
  //   for (unsigned j = 0; j < png_.height(); j++) {
  //     finalFrame.getPixel(i,j).h = png_.getPixel(i,j).h;
  //     finalFrame.getPixel(i,j).s = png_.getPixel(i,j).s;
  //     finalFrame.getPixel(i,j).l = png_.getPixel(i,j).l;
  //     finalFrame.getPixel(i,j).a = png_.getPixel(i,j).a;
  //   }
  // }
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal_, ColorPicker & colorPicker_) {
  /** @todo [Part 2] */
  traversal = &traversal_;
  colorPicker = &colorPicker_;
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) {
  /** @todo [Part 2] */
  Animation animation_;
  PNG* frame = new PNG(*finalFrame);
  animation_.addFrame(*frame);

  int i = 0;
  for (auto it = traversal->begin(); it != traversal->end(); ++it) {
  
    int x = (*it).x;
    int y = (*it).y;

    HSLAPixel color = colorPicker->getColor(x,y);
    HSLAPixel& currPixel = finalFrame->getPixel(x,y);

    currPixel = color;
    
    i++;
    if (i % frameInterval == 0) {
        animation_.addFrame(*finalFrame);
    }
  }

  animation_.addFrame(*finalFrame);

  for (unsigned i = 0; i < animation_.frameCount(); i++) {
    animation.addFrame(animation_.getFrame(i));
  }

  return animation;
}
