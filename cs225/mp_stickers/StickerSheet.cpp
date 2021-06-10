
#include "StickerSheet.h"
#include <iostream>


StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    maximum_ = max;
    imageArray_ = new Image[maximum_];
    xArray_ = new unsigned int[maximum_];
    yArray_ = new unsigned int[maximum_];

    base_ = picture;

    count_ = 0;

    sheetWidth_ = base_.width();
    sheetHeight_ = base_.height();
}

StickerSheet::StickerSheet (const StickerSheet &other) {
    imageArray_ = NULL;
    xArray_= NULL;
    yArray_ = NULL;
    _copy(other);
}
    
StickerSheet::~StickerSheet () {
    delete[] imageArray_;
    delete[] xArray_;
    delete[] yArray_;
}

void StickerSheet::_copy(StickerSheet const & other) {
    // Clear self
    delete[] imageArray_;
    delete[] xArray_;
    delete[] yArray_;

    // Copy `other` to self
    maximum_ = other.getMax();
    count_ = other.getCount();
    sheetWidth_ = other.getSheetWidth();
    sheetHeight_ = other.getSheetHeight();

    base_ = other.getBase();
    imageArray_ = new Image[maximum_+1];
    xArray_ = new unsigned int[maximum_+1];
    yArray_ = new unsigned int[maximum_+1];

    for (unsigned i = 0; i < count_; i++) {    
        imageArray_[i] = *(other.getSticker(i));
        xArray_[i] = other.getX(i);
        yArray_[i] = other.getY(i);
    }
}

StickerSheet const & StickerSheet::operator= (const StickerSheet & other) {
    if (this != &other) { _copy(other); }
    return *this;
}

bool StickerSheet::operator== (StickerSheet const & other) const {
    if ( maximum_ != other.getMax() ) { return false; }
    if ( count_ != other.getCount() ) { return false; }

    for (unsigned i = 0; i < maximum_; i++) {
        if (imageArray_[i] != *(other.getSticker(i))
            || xArray_[i] != other.getX(i)
            || yArray_[i] != other.getY(i) ) { return false; }
    }

    return true;
}

bool StickerSheet::operator!= (StickerSheet const & other) const {
    return !(*this == other);
}

void StickerSheet::updateWidth() {
    Image firstImage = base_;
    int firstVal = 0;
    for (unsigned i = 0; i < count_; i++) {
        Image secondImage = imageArray_[i];
        int secondVal = xArray_[i];

        if ( secondVal + secondImage.width() > firstVal + firstImage.width() ) {
            firstImage = secondImage;
            firstVal = secondVal;
        }
    }
    sheetWidth_ = firstVal + firstImage.width();
}

void StickerSheet::updateHeight() {
    Image firstImage = base_;
    int firstVal = 0;
    for (unsigned i = 0; i < count_; i++) {
        Image secondImage = imageArray_[i];
        int secondVal = yArray_[i];

        if ( secondVal + secondImage.height() > firstVal + firstImage.height() ) {
            firstImage = secondImage;
            firstVal = secondVal;
        }
    }
    sheetHeight_ = firstVal + firstImage.height();
}

void StickerSheet::changeMaxStickers (unsigned max) {
    maximum_ = max;
    Image* newImage = new Image[max+1];
    unsigned* newX = new unsigned[max+1];
    unsigned* newY = new unsigned[max+1];

    if (max < count_) 
        count_ = max;

    for (unsigned i = 0; i < count_; i++) {
        newImage[i] = imageArray_[i];
        newX[i] = xArray_[i];
        newY[i] = yArray_[i];
    }

    imageArray_ = newImage;
    xArray_ = newX;
    yArray_ = newY;

    if (max == count_) {
        updateWidth();
        updateHeight();
    }
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
    if ( count_ + 1 > maximum_) { return -1; }

    imageArray_[count_] = sticker;
    xArray_[count_] = x;
    yArray_[count_] = y;

    if ( x + sticker.width() > sheetWidth_ ) 
        sheetWidth_ = x + sticker.width(); 
    if ( y + sticker.height() > sheetHeight_ )
        sheetHeight_ = y + sticker.height();

    count_++;
    return count_ - 1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index >= count_ || index < 0) { return false; }

    Image& moved = imageArray_[index];
    unsigned oldX = xArray_[index];
    unsigned oldY = yArray_[index];

    xArray_[index] = x;
    yArray_[index] = y;

    if ( oldX + moved.width() == sheetWidth_) 
        updateWidth();
    if ( oldY + moved.height() > sheetHeight_) 
        updateHeight();

    return true;
}

void StickerSheet::removeSticker (unsigned index) {
    if (0 <= index && index < count_) {

        Image& removed = imageArray_[index];
        unsigned x = xArray_[index];
        unsigned y = yArray_[index];

        for (unsigned i = index; i < count_-1; i++) {
            imageArray_[i] = imageArray_[i+1];
            xArray_[i] = xArray_[i+1];
            yArray_[i] = yArray_[i+1];
        }
        count_--;
    
        if ( x + removed.width() == sheetWidth_)
            updateWidth();
        if ( y + removed.height() == sheetHeight_)
            updateHeight();
        
    }
}

Image * StickerSheet::getSticker (unsigned index) const {
    if (index >= count_ || index < 0)
        return NULL;

    Image* sticker = &imageArray_[index];
    return sticker;
}

Image StickerSheet::render () const {
    Image* sheet = new Image(sheetWidth_, sheetHeight_);

    for (unsigned x = 0; x < base_.width(); x++) {
        for (unsigned y = 0; y < base_.height(); y++) {
            sheet->getPixel(x,y) = base_.getPixel(x,y); 
        }
    }

    for (unsigned i = 0; i < count_; i++) {
        Image pic = imageArray_[i];
        unsigned xCorner = xArray_[i];
        unsigned yCorner = yArray_[i];

        for (unsigned x = 0; x < pic.width(); x++) {
            for (unsigned y = 0; y < pic.height(); y++) {
                if (pic.getPixel(x,y).a != 0) 
                    sheet->getPixel(x + xCorner,y + yCorner) = pic.getPixel(x,y); 
            }
        }
    }
    return *sheet;
}

Image StickerSheet::getBase() const {
    Image newBase = base_;
    return newBase;
    // return base_;
}
unsigned StickerSheet::getX (unsigned index) const {
    return xArray_[index];
}
unsigned StickerSheet::getY (unsigned index) const {
    return yArray_[index];
}
unsigned StickerSheet::getMax() const {
    return maximum_;
}
unsigned StickerSheet::getCount() const {
    return count_;
}
unsigned StickerSheet::getSheetWidth() const {
    return sheetWidth_;
}
unsigned StickerSheet::getSheetHeight() const {
    return sheetHeight_;
}

