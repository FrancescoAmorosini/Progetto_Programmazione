//
// Created by Francesco Amorosini on 22/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include "GameCharacter.h"
#include "Weapon.h"




class Enemy: virtual public GameCharacter, public DrawableObject{
public:
    Enemy(float x, float y, CharacterClass role, int HP, int atk,  int sightRadius, float evade=1, float critical=1);

    void updatePosition() override;
    Weapon* dropWeapon(WeaponType weaponType);
    void fight(GameCharacter* enemy) override;

    sf::Clock walkingTime;
    int static dropChance;
private:
    int sightRadius;
    std::string name;
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
