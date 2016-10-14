//
// Created by Francesco Amorosini on 08/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_TILE_H
#define PROGETTO_PROGRAMMAZIONE_TILE_H

#include "DrawableObject.h"


class Tile : public DrawableObject {
private:
    bool walkable;

public:
    Tile() {
        walkable=true;
        rect.setSize(sf::Vector2f(32, 32));
        rect.setFillColor(sf::Color::Magenta);
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

    bool isWalkable() const {
        return walkable;
    }

    void setWalkabe(bool walkable) {
        Tile::walkable = walkable;
    }
};


#endif //PROGETTO_PROGRAMMAZIONE_TILE_H
