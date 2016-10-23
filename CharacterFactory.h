//
// Created by Francesco Amorosini on 13/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_CHARACTERFACTORY_H
#define PROGETTO_PROGRAMMAZIONE_CHARACTERFACTORY_H

#include "WeaponFactory.h"
#include "Enemy.h"



class CharacterFactory {
public:
    static  PlayableCharacter* createCharacter(float x, float y, const CharacterClass type, const std::string name)
                                                                                        throw(std::invalid_argument);
    static std::vector<Enemy*> createEnemyArray(int size, const CharacterClass type, int HP, int atk);
};

#endif //PROGETTO_PROGRAMMAZIONE_CHARACTERFACTORY_H
