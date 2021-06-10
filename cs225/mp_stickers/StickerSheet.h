/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
 
class StickerSheet{

    public:

        StickerSheet (const Image &picture, unsigned max);
    
        ~StickerSheet ();
    
        StickerSheet (const StickerSheet &other);
    
        StickerSheet const & operator= (const StickerSheet &other);

        bool operator== (StickerSheet const & other) const;

        bool operator!= (StickerSheet const & other) const;      

        void changeMaxStickers (unsigned max);
        
        int addSticker (Image &sticker, unsigned x, unsigned y);
        
        bool translate (unsigned index, unsigned x, unsigned y);
        
        void removeSticker (unsigned index);
        
        Image * getSticker (unsigned index) const;

        Image getBase() const;
        
        Image render () const;

        unsigned int getX (unsigned index) const;
        unsigned int getY (unsigned index) const;
        unsigned getMax() const;
        unsigned getCount() const;
        unsigned getSheetWidth() const;
        unsigned getSheetHeight() const;       

        void updateWidth();
        void updateHeight();

    private:
        unsigned maximum_;
        unsigned count_;
        unsigned sheetWidth_;
        unsigned sheetHeight_;

        Image base_;
        Image* imageArray_;
        unsigned* xArray_;
        unsigned* yArray_;

        void _copy(StickerSheet const & other);

};