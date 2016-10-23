//
// Created by Francesco Amorosini on 26/08/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_WEAPONFACTORY_H
#define PROGETTO_PROGRAMMAZIONE_WEAPONFACTORY_H

#include "Weapon.h"
#include "PlayableCharacter.h"

class WeaponFactory {
public:
    static WeaponType matchHeroWeapon(CharacterClass role);
    static Weapon* createWeapon(float posX, float posY, int strenght, bool rare=false, bool legendary=false);
    static WeaponType heroWeaponType;

};


#endif //PROGETTO_PROGRAMMAZIONE_WEAPONFACTORY_H
