//
// Created by Francesco Amorosini on 08/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_TILE_H
#define PROGETTO_PROGRAMMAZIONE_TILE_H

#include "DrawableObject.h"
#include "RNG.h"


class Tile : public DrawableObject {
public:
    Tile(){}
    Tile(int x,int y, std::string tiletype) {
        walkable=true;
        rect.setSize(sf::Vector2f(32, 32));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Magenta);
        sprite.setPosition(rect.getPosition());

        //[x,x] = Grass tile
        if (tiletype[0] == 'x' && tiletype[2] == 'x') {
            sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
            if (RNG::throwCoin(20))
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            else if (RNG::throwCoin(20))
                sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
            else if (RNG::throwCoin((20)))
                sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));

        }
        //[X,U] = Route Up
        if (tiletype[0] == 'X' && tiletype[2] == 'U')
            sprite.setTextureRect(sf::IntRect(32* 6, 32, 32, 32));
        //[X,D] = Route Down
        if (tiletype[0] == 'X' && tiletype[2] == 'D')
            sprite.setTextureRect(sf::IntRect(32* 6, 32* 3, 32, 32));
        //[X,L] = Route Left
        if (tiletype[0] == 'X' && tiletype[2] == 'L')
            sprite.setTextureRect(sf::IntRect(32* 5, 32* 2, 32, 32));
        //[X,R] = Route Right
        if (tiletype[0] == 'X' && tiletype[2] == 'R')
            sprite.setTextureRect(sf::IntRect(32* 7, 32* 2, 32, 32));
        //[X,1] = Corner Route UpLeft
        if (tiletype[0] == 'X' && tiletype[2] == '1')
            sprite.setTextureRect(sf::IntRect(32* 5, 32, 32, 32));
        //[X,2] = Corner Route UpRight
        if (tiletype[0] == 'X' && tiletype[2] == '2')
            sprite.setTextureRect(sf::IntRect(32* 7, 32, 32, 32));
        //[X,3] = Corner Route BotLeft
        if (tiletype[0] == 'X' && tiletype[2] == '3')
            sprite.setTextureRect(sf::IntRect(32* 5, 32* 3, 32, 32));
        //[X,4] = Corner Route  BotRight
        if (tiletype[0] == 'X' && tiletype[2] == '4')
            sprite.setTextureRect(sf::IntRect(32* 7, 32* 3, 32, 32));
        //[X,5] = Plain Route
        if (tiletype[0] == 'X' && tiletype[2] == '5')
            sprite.setTextureRect(sf::IntRect(32*6, 32*2, 32, 32));


    }

    bool isWalkable() const {
        return walkable;
    }

    void setWalkabe(bool walkable) {
        Tile::walkable = walkable;
    }

    bool walkable;
};


#endif //PROGETTO_PROGRAMMAZIONE_TILE_H
