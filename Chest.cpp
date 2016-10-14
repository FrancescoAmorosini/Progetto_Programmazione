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
}

Chest::Chest(float posX, float posY, Orb *o) : orb(o) {
    weapon= nullptr;

    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(posX, posY);
    rect.setFillColor(sf::Color::Blue);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    sprite.setPosition(rect.getPosition());

    orb->rect.setPosition((rect.getPosition()));
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

