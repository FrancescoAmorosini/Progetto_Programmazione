//
// Created by Francesco Amorosini on 26/08/16.
//



#ifndef PROGETTO_PROGRAMMAZIONE_WALL_H
#define PROGETTO_PROGRAMMAZIONE_WALL_H
#include "Tile.h"

class Wall : public Tile{

public:
    Wall(int x, int y, bool breakable=false) : posX(x), posY(y), breakable(breakable) {
        Tile::setWalkabe(false);
        rect.setSize(sf::Vector2f(32, 32));
        rect.setPosition(x,y);
        rect.setFillColor(sf::Color::Black);
        sprite.setPosition(rect.getPosition());
        sprite.setTextureRect(sf::IntRect(224, 4*32, 32, 32));}

    int posX;
    int posY;
    bool breakable;
};

#endif //PROGETTO_PROGRAMMAZIONE_WALL_H