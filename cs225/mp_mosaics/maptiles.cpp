/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> pts;
    for (int i = 0; i < (int)theTiles.size(); i++) {
        pts.push_back( convertToXYZ( theTiles[i].getAverageColor() ) );
    }
    KDTree<3> tree(pts);

    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns()); 

    for (int row = 0; row < theSource.getRows(); row++) {
        for (int col = 0; col < theSource.getColumns(); col++) {
            Point<3> pt = tree.findNearestNeighbor( convertToXYZ ( theSource.getRegionColor(row, col) ) );

            for (int j = 0; j < (int)theTiles.size(); j++) {
                if (pt == convertToXYZ( theTiles[j].getAverageColor() )) {
                    TileImage* pTile = &(theTiles[j]);
                    canvas->setTile(row, col, pTile);
                    break;
                };
            }
        }
    }

    return canvas;
}

