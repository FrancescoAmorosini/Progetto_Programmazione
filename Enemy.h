//
// Created by Francesco Amorosini on 22/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include "GameCharacter.h"
#include "WeaponFactory.h"
#include "PlayableCharacter.h"
#include "Spell.h"


class Enemy: virtual public GameCharacter, public DrawableObject{
public:
    Enemy(float x, float y, CharacterClass role, int HP, int atk, int evade=1, int critical=1);
    //Strategy method
    void move();
    void turnAround(PlayableCharacter* hero);
    void chaseHero(PlayableCharacter* hero);
    Spell* shootSpell();

    Weapon* dropWeapon();
    void fight(GameCharacter* hero) override;
    void updatePosition() override;

    bool aggroed=false;
    sf::Clock walkingTime;
    int static dropChance;
    int speed = speedMovement -1;
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
