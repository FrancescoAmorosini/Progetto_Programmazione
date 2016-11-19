//
// Created by francesco amorosini on 18/11/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_STRATEGY_H
#define PROGETTO_PROGRAMMAZIONE_STRATEGY_H

#include "PlayableCharacter.h"
#include "Enemy.h"

class Enemy;

class Strategy{
public:
    virtual void movementBehavior(PlayableCharacter*hero, Enemy* enemy) =0;
    virtual ~Strategy(){}
};

class ChaseHero : public Strategy{
public:
    virtual void movementBehavior(PlayableCharacter* hero, Enemy* enemy) override;

};

class Flee : public Strategy{
public:
    virtual void movementBehavior(PlayableCharacter* hero, Enemy* enemy) override;
};

class TurnAround : public Strategy{
public:
    virtual void movementBehavior(PlayableCharacter* hero, Enemy* enemy) override;
};

#endif //PROGETTO_PROGRAMMAZIONE_STRATEGY_H
