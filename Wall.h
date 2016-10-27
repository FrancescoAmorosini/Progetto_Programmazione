//
// Created by Francesco Amorosini on 26/08/16.
//



#ifndef PROGETTO_PROGRAMMAZIONE_WALL_H
#define PROGETTO_PROGRAMMAZIONE_WALL_H
#include "Tile.h"

class Wall : public Tile{

public:
    Wall(int x, int y, std::string walltype) : posX(x), posY(y) {
        Tile::setWalkabe(false);
        rect.setSize(sf::Vector2f(32, 32));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Black);
        sprite.setPosition(rect.getPosition());
        //0,0 = stone wall
        if (walltype[0] == '0' && walltype[2] == '0')
            sprite.setTextureRect(sf::IntRect(224, 4 * 32, 32, 32));
        //0,1 = breakable stone wall
        if (walltype[0] == '0' && walltype[2] == '1') {
            sprite.setTextureRect(sf::IntRect(224, 4 * 32, 32, 32));
            sprite.setColor(sf::Color(255, 255, 255, 180));
            breakable = true;
        }
    }

    int posX;
    int posY;
    bool breakable= false;
};

#endif //PROGETTO_PROGRAMMAZIONE_WALL_H