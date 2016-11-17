//
// Created by Francesco Amorosini on 26/06/16.
//

#include "Chest.h"

Chest::Chest(float posX, float posY, Weapon *w) : weapon(w){
    orb=nullptr;

    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(posX, posY);
    rect.setFillColor(sf::Color::White);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setPosition(rect.getPosition());

    weapon->rect.setPosition(rect.getPosition());
    text.setCharacterSize(16);
    text.setPosition(rect.getPosition().x - 20 , rect.getPosition().y - 20);

    if(w->isLegendary()) {
        text.setString("STR: " + std::to_string(weapon->getStrenght()) + ",  LEGENDARY!  ");
        text.setFillColor(sf::Color::Cyan);
    }
    else if(w->isRare()) {
        text.setString("STR: " + std::to_string(weapon->getStrenght()) + ",  RARE!  ");
        text.setFillColor(sf::Color(255,128,0));
    }
    else
        text.setString("STR: " + std::to_string(weapon->getStrenght()));
}

Chest::Chest(float posX, float posY, Orb *o) : orb(o) {
    weapon= nullptr;

    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(posX, posY);
    rect.setFillColor(sf::Color::Blue);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setPosition(rect.getPosition());

    orb->rect.setPosition((rect.getPosition()));

    text.setCharacterSize(16);
    text.setPosition(rect.getPosition().x - 20 , rect.getPosition().y - 20);

    switch(o->getOrbColor()) {
        case Color::red:
            text.setFillColor(sf::Color::Magenta);
            text.setString("Red Orb");
            break;
        case Color::blue:
            text.setFillColor(sf::Color::Blue);
            text.setString("Blue Orb");
            break;
        case Color::green:
            text.setFillColor(sf::Color::Green);
            text.setString("Green Orb");
            break;
        case Color::yellow:
            text.setFillColor(sf::Color::Yellow);
            text.setString("Yellow Orb");
            break;
        case Color::purple:
            text.setFillColor(sf::Color(127,0,255));
            text.setString("Purple Orb");
            break;
    }
}

Chest::~Chest() {
        if (weapon != nullptr)
            delete weapon;
        if (orb != nullptr)
            delete orb;
}

void Chest::openChest(PlayableCharacter* hero) {
    if (getOrb()) {
        hero->setInventory(getOrb());
        setOrb(nullptr);
    } else if (getWeapon()) {
        Weapon *w = hero->getWeapon();
        hero->setWeapon(weapon);
        setWeapon(w);
        //Update text
        if(weapon->isLegendary()) {
            text.setString("STR: " + std::to_string(weapon->getStrenght()) + ",  LEGENDARY!  ");
            text.setFillColor(sf::Color::Cyan);
        }
        else if(weapon->isRare()) {
            text.setString("STR: " + std::to_string(weapon->getStrenght()) + ",  RARE!  ");
            text.setFillColor(sf::Color(255,128,0));
        }
        else {
            text.setString("STR: " + std::to_string(weapon->getStrenght()));
            text.setFillColor(sf::Color::White);
        }
    }

    sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
    hero->addChestOpened();
}

Weapon* Chest::getWeapon() const {
    return weapon;
}

void Chest::setWeapon(Weapon *weapon) {
    Chest::weapon = weapon;
}

Orb* Chest::getOrb() const {
    return orb;
}

void Chest::setOrb(Orb *orb) {
    Chest::orb = orb;
}

sf::Clock Chest::objectTaken;
sf::Time Chest::delay= sf::seconds(1);