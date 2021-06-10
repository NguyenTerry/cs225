#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image base;
  Image sticker0;
  Image sticker1;
  Image sticker2;

  base.readFromFile("base.png");
  sticker0.readFromFile("sticker0.png");
  // sticker0.scale(.3);
  sticker1.readFromFile("sticker1.png");
  // sticker1.scale(.4);
  sticker2.readFromFile("sticker2.png");
  // sticker0.scale(.5);

  unsigned sticker0x = 307;
  unsigned sticker0y = 204;

  unsigned sticker1x = 507;
  unsigned sticker1y = 354;
  
  unsigned sticker2x = 155;
  unsigned sticker2y = 30;

  StickerSheet myImage = StickerSheet(base, 5);
  myImage.addSticker(sticker1, sticker1x, sticker1y);
  myImage.addSticker(sticker2, sticker2x, sticker2y);
  myImage.addSticker(sticker0, sticker0x, sticker0y);

  myImage.render().writeToFile("myImage.png");

  return 0;
}
