//
// Created by Francesco Amorosini on 26/08/16.
//

#include "WeaponFactory.h"

WeaponType WeaponFactory::matchHeroWeapon(CharacterClass role) {
    if (CharacterClass::Thief == role)
        return WeaponType::Dagger;
    else if (CharacterClass::Knight == role)
        return WeaponType::Sword;
    else
        return WeaponType::Staff;
}

Weapon* WeaponFactory::createWeapon(float posX, float posY, int strenght, bool rare, bool legendary) {
    return new Weapon(posX,posY,strenght,heroWeaponType,rare,legendary);
}

WeaponType WeaponFactory::heroWeaponType;