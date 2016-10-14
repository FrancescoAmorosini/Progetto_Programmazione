//
// Created by Francesco Amorosini on 08/10/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_HEART_H
#define PROGETTO_PROGRAMMAZIONE_HEART_H

#include "DrawableObject.h"
#include "PlayableCharacter.h"

class Heart : public DrawableObject{
public:
    Heart(int x, int y){
        rect.setSize(sf::Vector2f(32, 32));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Red);
        sprite.setPosition(rect.getPosition());
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    }

    void restoreHealth(PlayableCharacter* hero){
        hero->heal(25);
    }
};
#endif //PROGETTO_PROGRAMMAZIONE_HEART_H
