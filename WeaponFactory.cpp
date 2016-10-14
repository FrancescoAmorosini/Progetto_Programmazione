//
// Created by Francesco Amorosini on 26/08/16.
//

#include "WeaponFactory.h"

WeaponType WeaponFactory::matchHeroWeapon(PlayableCharacter* hero){
    if(hero->getRole() == CharacterClass::Thief)
        return WeaponType::Dagger;
    if(hero->getRole() == CharacterClass::Knight)
        return WeaponType::Sword;
    if(hero->getRole() == CharacterClass::Lancer)
        return WeaponType::Spear;
    else
        return WeaponType::Staff;
}

Weapon* WeaponFactory::createWeapon(int posX, int posY, int strenght, WeaponType w, bool rare, bool legendary) {
    return new Weapon(posX,posY,strenght,w,rare,legendary);
}