//
// Created by Francesco Amorosini on 08/07/16.
//

#include "Map.h"
Map::Map(int width, int height) : width(width), height(height) {
    if(width <= 0 || height <= 0)
        throw std::invalid_argument("Error: invalid map coordinates");
    else
        for(int i=0; i<width; i++){
            for(int j=0; j<height;j++)
                buffer.push_back(new Tile (i*32, j*32, "x,x"));
        }
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

