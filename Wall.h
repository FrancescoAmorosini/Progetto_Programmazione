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

        //[0,U] = Upper wall
        if (walltype[0] == '0' && walltype[2] == 'U')
            sprite.setTextureRect(sf::IntRect(32*2, 32*2, 32, 32));
        if (walltype[0] == '0' && walltype[2] == 'u') {
            sprite.setTextureRect(sf::IntRect(32*2, 32*3, 32, 32));
            walkable=true;
        }
        //[0,L] = Left wall
        if (walltype[0] == '0' && walltype[2] == 'L')
            sprite.setTextureRect(sf::IntRect(32*0, 32*2, 32, 32));
        //[0,R] = Right wall
        if (walltype[0] == '0' && walltype[2] == 'R')
            sprite.setTextureRect(sf::IntRect(32*1, 32*2, 32, 32));
        //[0,D] = Bottom wall
        if (walltype[0] == '0' && walltype[2] == 'D')
            sprite.setTextureRect(sf::IntRect(32*0, 32*3, 32, 32));
        //[0,1] = Upper Left wall
        if (walltype[0] == '0' && walltype[2] == '1')
            sprite.setTextureRect(sf::IntRect(32*3, 32*2, 32, 32));
        //[0,2] = Upper Right wall
        if (walltype[0] == '0' && walltype[2] == '2')
            sprite.setTextureRect(sf::IntRect(32*4, 32*2 + 2, 32, 32));
        //[0,3] = Bottom Left wall
        if (walltype[0] == '0' && walltype[2] == '3')
            sprite.setTextureRect(sf::IntRect(32*3, 32*3 + 4, 32, 32));
        //[0,4] = Bottom Right wall
        if (walltype[0] == '0' && walltype[2] == '4')
            sprite.setTextureRect(sf::IntRect(32*4, 32*3, 32, 32));


        //[1,U] = Upper river
        if (walltype[0] == '1' && walltype[2] == 'U')
            sprite.setTextureRect(sf::IntRect(32*4, 32*0, 32, 32));
        //[1,D] = Bottom river
        if (walltype[0] == '1' && walltype[2] == 'D')
            sprite.setTextureRect(sf::IntRect(32*5, 32*0, 32, 32));
        //[1,L] = Left river
        if (walltype[0] == '1' && walltype[2] == 'L')
            sprite.setTextureRect(sf::IntRect(32*7, 32*0, 32, 32));
        //[1,R] = Right river
        if (walltype[0] == '1' && walltype[2] == 'R')
            sprite.setTextureRect(sf::IntRect(32*6, 32*0, 32, 32));
        //[1,1] = Upper Left river
        if (walltype[0] == '1' && walltype[2] == '1')
            sprite.setTextureRect(sf::IntRect(32*2, 32*0, 32, 32));
        //[1,2] = Upper Right river
        if (walltype[0] == '1' && walltype[2] == '2')
            sprite.setTextureRect(sf::IntRect(32*3, 32*0, 32, 32));
        //[1,3] = Bottom Left river
        if (walltype[0] == '1' && walltype[2] == '3')
            sprite.setTextureRect(sf::IntRect(32*2, 32*1, 32, 32));
        //[1,4] = Bottom Right river
        if (walltype[0] == '1' && walltype[2] == '4')
            sprite.setTextureRect(sf::IntRect(32*3, 32*1, 32, 32));
        //[1,5] = Plain Water
        if (walltype[0] == '1' && walltype[2] == '5')
            sprite.setTextureRect(sf::IntRect(32*4, 32*1, 32, 32));

        //[2,0] = Simple Wall
        if (walltype[0] == '2' && walltype[2] == '0')
            sprite.setTextureRect(sf::IntRect(32*1, 32*3, 32, 32));
        //[2,1] = Simple Breakable Wall
        if (walltype[0] == '2' && walltype[2] == '1') {
            sprite.setTextureRect(sf::IntRect(32 * 1, 32 * 3, 32, 32));
            sprite.setColor(sf::Color(255,100,100,255));
            breakable=true;
        }
    }

    int posX;
    int posY;
    bool breakable= false;
};

#endif //PROGETTO_PROGRAMMAZIONE_WALL_H