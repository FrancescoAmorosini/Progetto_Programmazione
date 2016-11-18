//
// Created by Francesco Amorosini on 22/06/16.
//

#include "Orb.h"

Orb::Orb(float x, float y, Color c) :orbColor(c) {

    rect.setSize(sf::Vector2f(21, 21));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::White);
    switch (c) {
        case Color::red:
            sprite.setTextureRect(sf::IntRect(21 * 3, 0, 21, 21));
            text.setString("+5 ATK");
            text.setFillColor(sf::Color::Red);
            break;
        case Color::blue:
            sprite.setTextureRect(sf::IntRect(21, 0, 21, 21));
            text.setString("+30 HP");
            text.setFillColor(sf::Color::Blue);
            break;
        case Color::green:
            sprite.setTextureRect(sf::IntRect(0, 0, 21, 21));
            text.setString("+1 CRIT");
            text.setFillColor(sf::Color::Green);
            break;
        case Color::yellow:
            sprite.setTextureRect(sf::IntRect(21 * 2, 0, 21, 21));
            text.setString("WEAPON UPGRADE!");
            text.setFillColor(sf::Color::Yellow);
            break;
        case Color::purple:
            sprite.setTextureRect(sf::IntRect(21 * 4, 0, 21, 21));
            text.setString("+1 EVADE");
            text.setFillColor(sf::Color(255,100,255));
            break;
    }
    text.setCharacterSize(15);
    sprite.setPosition(rect.getPosition());
}

void Orb::useOrb(PlayableCharacter *hero) {
    switch(getOrbColor()){
        case Color::blue:
            hero->setmaxHP(hero->getmaxHP()+30);
            hero->setHP(hero->getHP() + 30);
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
    hero->orbUsedText=text;
    hero->addOrbUsed();
    hero->orbUsedText.setString("");
}

Color Orb::getOrbColor() const {
    return orbColor;
}

sf::Clock Orb::usedOrb;