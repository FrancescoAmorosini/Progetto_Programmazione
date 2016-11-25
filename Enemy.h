//
// Created by Francesco Amorosini on 22/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include "GameCharacter.h"
#include "WeaponFactory.h"
#include "PlayableCharacter.h"
#include "Spell.h"
#include "Strategy.h"

class Strategy;

class Enemy: virtual public GameCharacter, public DrawableObject{
public:
    Enemy(float x, float y, CharacterClass role, int HP, int atk, int evade=1, int critical=1);
    //Strategy method
    void move(PlayableCharacter* hero);

    void setAggroed(bool aggroed);
    void setStrategy(Strategy* s);
    void setHP (int HP) override;
    Spell* shootSpell();

    Weapon* dropWeapon();
    void fight(GameCharacter* hero) override;
    void updatePosition() override;

    sf::Clock walkingTime;
    int static dropChance;
    int speed = speedMovement -2;
    Face previousFace=Face::Down;

private:
    bool aggroed=false;
    Strategy* behavior;
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
