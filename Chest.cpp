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
        text.setColor(sf::Color(127, 0, 255));
    }
    else if(w->isRare()) {
        text.setString("STR: " + std::to_string(weapon->getStrenght()) + ",  RARE!  ");
        text.setColor(sf::Color(255,128,0));
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
            text.setColor(sf::Color::Magenta);
            text.setString("Red Orb");
            break;
        case Color::blue:
            text.setColor(sf::Color::Blue);
            text.setString("Blue Orb");
            break;
        case Color::green:
            text.setColor(sf::Color::Green);
            text.setString("Green Orb");
            break;
        case Color::yellow:
            text.setColor(sf::Color::Yellow);
            text.setString("Yellow Orb");
            break;
        case Color::purple:
            text.setColor(sf::Color(127,0,255));
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
    } else {
        Weapon* w= hero->getWeapon();
        hero->setWeapon(weapon);
        setWeapon(w);
    }
    sprite.setTextureRect(sf::IntRect(32,0,32,32));
    text.setString("");
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