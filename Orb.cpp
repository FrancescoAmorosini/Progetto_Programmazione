//
// Created by Francesco Amorosini on 22/06/16.
//

#include "Orb.h"

Orb::Orb(float x, float y, Color c) :orbColor(c) {

    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::White);
    switch(c) {
        case Color::red:
            sprite.setTextureRect(sf::IntRect(7*32, 3*32, 32, 32));
            text.setString("+5 ATK");
            break;
        case Color::blue:
            sprite.setTextureRect(sf::IntRect(6*32, 7*32, 32, 32));
            text.setString("+30 HP");
            break;
        case Color::green:
            sprite.setTextureRect(sf::IntRect(6*32, 3*32, 32, 32));
            text.setString("+1 CRIT");
            break;
        case Color::yellow:
            sprite.setTextureRect(sf::IntRect(6*32, 1*32, 32, 32));
            text.setString("WEAPON UPGRADE!");
            break;
        case Color::purple:
            sprite.setTextureRect(sf::IntRect(7*32, 0, 32, 32));
            text.setString("+1 EVADE");
            break;
    }
    sprite.setPosition(rect.getPosition());
}

std::string Orb::useOrb(PlayableCharacter *hero) {
    switch(getOrbColor()){
        case Color::blue:
            hero->setmaxHP(hero->getmaxHP()+30);
            break;
        case Color::red:
            hero->setAtk(hero->getAtk() + 5);
            break;
        case Color::green:
            hero->setCritical(hero->getCritical() + 1);
            break;
        case Color::purple:
            hero->setEvade(hero->getEvade() + 1);
            break;
        case Color::yellow:
            if(!hero->getWeapon()->isRare())
                hero->getWeapon()->setRare(true);
            else
                hero->getWeapon()->setLegendary(true);
            break;
    }
    return text.getString();
}

Color Orb::getOrbColor() const {
    return orbColor;
}

