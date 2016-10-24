//
// Created by Francesco Amorosini on 22/06/16.
//

#include "PlayableCharacter.h"


PlayableCharacter::PlayableCharacter(float x, float y, CharacterClass r, std::string name, Weapon* w,int HP, int atk, int evade, int critical) throw(std::invalid_argument) :
        GameCharacter(r,HP,atk,evade,critical),name(name), weapon(w){
    rect.setSize(sf::Vector2f(32, 32));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Red);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    text.setString(name);
    text.setCharacterSize(16);
}

PlayableCharacter::~PlayableCharacter() {
    if(weapon!= nullptr)
        delete weapon;
    inventory.erase(inventory.begin(),inventory.end());
}

void PlayableCharacter::updatePosition() {
    sprite.setPosition(rect.getPosition());
    int long delay = name.length() * 2;
    if (name.length() < 5)
        delay = -name.length();
    text.setPosition(rect.getPosition().x - delay, rect.getPosition().y - 20);
    if (weapon)
        weapon->rect.setPosition(rect.getPosition());
}

void PlayableCharacter::fight(GameCharacter* enemy) {
    int damage= getAtk() + weapon->useWeapon();
    if(RNG::throwCoin(10 - getCritical()) && !weapon->isLegendary())                     // critical=1 -> 10% critical chance
        damage+= damage/2;
    if(RNG::throwCoin(10 - enemy->getEvade()))                                          //enemy.evade=1 -> 10% evade chance
        damage=0;
    if(damage){
        enemy->setHP(enemy->getHP()-damage);
        if(weapon->isRare())
            heal(damage/3);
    }
}

const std::string PlayableCharacter::getName() const {
    return this->name;
}

void PlayableCharacter::setName(const std::string &name) {
    PlayableCharacter::name = name;
}

Weapon* PlayableCharacter::getWeapon() const {
    return weapon;
}

void PlayableCharacter::setWeapon(Weapon *weapon) {
    weapon->rect.setPosition(rect.getPosition());
    this->weapon = weapon;
}

const Orb* PlayableCharacter::getInventory(int index) const throw(RangeException) {
    if (index>=0 && index<inventory.size()) {
        return inventory[index];
    }
    else
        throw RangeException("Error: invalid inventory index",0, static_cast<unsigned int>(inventory.size()),index);

}

void PlayableCharacter::setInventory(Orb* o){
    inventory.push_back(o);
}


