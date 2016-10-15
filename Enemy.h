//
// Created by Francesco Amorosini on 22/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include "GameCharacter.h"
#include "Weapon.h"
#include "PlayableCharacter.h"
#include "Spell.h"


class Enemy: virtual public GameCharacter, public DrawableObject{
public:
    Enemy(float x, float y, CharacterClass role, int HP, int atk,  int sightRadius, float evade=1, float critical=1);

    void updatePosition() override;
    Weapon* dropWeapon(WeaponType weaponType);
    void fight(GameCharacter* hero) override;
    void chaseHero(PlayableCharacter* hero);
    Spell* shootSpell();
    bool aggroed;

    sf::Clock walkingTime;
    int static dropChance;
    int sightRadius;
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
