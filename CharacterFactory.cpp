//
// Created by Francesco Amorosini on 13/07/16.
//

#include "CharacterFactory.h"

CharacterFactory::CharacterFactory() { }

GameCharacter* CharacterFactory::createCharacter(const CharacterClass type, const std::string name) throw(std::invalid_argument) {
    return nullptr;
}

std::vector<GameCharacter*> CharacterFactory::createEnemyArray(int size, CharacterClass type, int HP, int atk, int sightRadius) {
    std::vector<GameCharacter*> array;
    for(int i=0;i<size;i++)
        array.push_back(new Enemy(0,0,type,HP,atk,sightRadius));
    return array;
}