//
// Created by Francesco Amorosini on 13/07/16.
//

#include "CharacterFactory.h"

PlayableCharacter* CharacterFactory::createCharacter(float x, float y, const CharacterClass type, const std::string name)
                                                                                throw(std::invalid_argument) {
    switch (type) {
        case CharacterClass::Knight:
            return new PlayableCharacter(x, y, type, name, WeaponFactory::createWeapon(x, y, 10), 120, 12);
        case CharacterClass::Mage:
            return new PlayableCharacter(x, y, type, name, WeaponFactory::createWeapon(x, y, 10));
        case CharacterClass::Thief:
            return new PlayableCharacter(x, y, type, name, WeaponFactory::createWeapon(x, y, 10), 100, 2, 2);
        default:
            throw (std::invalid_argument("Error: invalid character type"));
    }
}

std::vector<Enemy*> CharacterFactory::createEnemyArray(int size, CharacterClass type, int HP, int atk) {
    std::vector<Enemy*> array;
    for(int i=0;i<size;i++)
        array.push_back(new Enemy(0,0,type,HP,atk));
    return array;
}