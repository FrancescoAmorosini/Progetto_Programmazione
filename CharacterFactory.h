//
// Created by Francesco Amorosini on 13/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_CHARACTERFACTORY_H
#define PROGETTO_PROGRAMMAZIONE_CHARACTERFACTORY_H

#ifndef Included_Character_H
#define Included_Character_H

#include "PlayableCharacter.h"
#include "Enemy.h"

#endif



class CharacterFactory {
public:
    CharacterFactory();
    virtual ~CharacterFactory(){}

    static GameCharacter* createCharacter(const CharacterClass type, std::string name) throw(std::invalid_argument);
    static std::vector<GameCharacter*> createEnemyArray(int size, const CharacterClass type, int HP, int atk, int sightRadius);
};

#endif //PROGETTO_PROGRAMMAZIONE_CHARACTERFACTORY_H
