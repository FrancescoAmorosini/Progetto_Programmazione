//
// Created by Francesco Amorosini on 08/07/16.
//

#include "Map.h"

Map::Map(int w, int h) throw(std::invalid_argument) : width(w),height(h) {
    if (w > 0 && h > 0) {
        for (int i = 0; i < w * h; i++)
            buffer.push_back(new Tile());

    } else
        throw (std::invalid_argument("Error: insert valid map dimensions"));
}
Map::~Map() {
    buffer.erase(buffer.begin(), buffer.end());
    wallBuffer.erase(wallBuffer.begin(), wallBuffer.end());
}

void Map::setTile(int x, int y, const bool walkable) throw(RangeException){
    if(x<0 || x>=width)
        throw RangeException("Error: invalid width coordinates",0,width-1,x);
    else if(y<0 || y>=height)
        throw RangeException("Error: invalid height coordinates",0,height-1,y);
    else
        buffer[x + y * width]->setWalkabe(walkable);
}

Tile* Map::getTile(int x, int y) throw(RangeException) {
    if(x<0 || x>=width)
        throw RangeException("Error: invalid width coordinates",0,width-1,x);
    else if(y<0 || y>=height)
        throw RangeException("Error: invalid height coordinates",0,height-1,y);
    else
        return buffer[x + y * width];
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

