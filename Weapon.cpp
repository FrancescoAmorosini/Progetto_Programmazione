//
// Created by Francesco Amorosini on 22/06/16.
//

#include "Weapon.h"

Weapon::Weapon(float x, float y, int strenght, WeaponType weapon, bool rare, bool legendary):
     strenght(strenght), weapon(weapon), rare(rare), legendary(legendary){
    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Yellow);
    sprite.setPosition(rect.getPosition());
    switch(weapon) {
        case WeaponType::Dagger:
            sprite.setTextureRect(sf::IntRect(2 * 32, 32, 32, 32));
            break;
        case WeaponType::Axe:
            sprite.setTextureRect(sf::IntRect(6 * 32, 0, 32, 32));
            break;
        case WeaponType::Staff:
            sprite.setTextureRect(sf::IntRect(6 * 32, 4 * 32, 32, 32));
            break;
    }

    text.setCharacterSize(20);
    text.setPosition(rect.getPosition().x -20 ,rect.getPosition().y -20);

    if(legendary)
       setLegendary(true);
    else if(rare)
        setRare(true);
    else
        text.setString("STR: " + std::to_string(strenght));

}

int Weapon::useWeapon() {
    int damage= getStrenght();
    int toll= getStrenght() % 13;
    if(RNG::throwCoin(2))
        damage+= RNG::throwDice(toll);
    else
        damage-=RNG::throwDice(toll);
    if(isLegendary())
        damage+=damage/2;
    return damage;
}

int Weapon::getStrenght() const {
    return strenght;
}

void Weapon::setStrenght(int strenght) {
    Weapon::strenght = strenght;
}

bool Weapon::isRare() const {
    return rare;
}

void Weapon::setRare(bool rare) {
    Weapon::rare = rare;
    if(rare){
        text.setFillColor(sf::Color(224,224,244));
        text.setString("STR: " + std::to_string(strenght) + ",  RARE!  ");
        }

}

bool Weapon::isLegendary() const {
    return legendary;
}

void Weapon::setLegendary(bool legendary) {
    Weapon::legendary = legendary;
    if(legendary) {
        text.setString("STR: " + std::to_string(strenght) + ",  LEGENDARY!  ");
        text.setFillColor(sf::Color(204,204,0));
    }
}

WeaponType Weapon::getWeapon() const {
    return weapon;
}


