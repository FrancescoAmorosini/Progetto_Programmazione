//
// Created by Francesco Amorosini on 08/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_MAP_H
#define PROGETTO_PROGRAMMAZIONE_MAP_H

#ifndef Included_RangeException_H
#define Included_RangeException_H

#include "RangeException.h"

#endif

#include <vector>
#include"Tile.h"
#include "Wall.h"


class Map {
public:
    Map(int width, int height);
    ~Map();

    void setTile(int w, int h, const bool walkable) throw(RangeException);
    Tile* getTile(int x, int y) throw(RangeException);
    int getWidth() const;
    int getHeight() const;

    std::vector<Wall*> wallBuffer;
    std::vector<Tile*> buffer;
    Tile* exit;
    bool levelCompleted=false;

private:
    int width;
    int height;


};



#endif //PROGETTO_PROGRAMMAZIONE_MAP_H
