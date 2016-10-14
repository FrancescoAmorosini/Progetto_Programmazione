//
// Created by Francesco Amorosini on 26/08/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_WEAPONFACTORY_H
#define PROGETTO_PROGRAMMAZIONE_WEAPONFACTORY_H

#ifndef Included_Weapon_H
#define Included_Weapon_H
#include "Weapon.h"
#endif

#ifndef Included_Character_H
#define Included_Character_H

#include "PlayableCharacter.h"

#endif

class WeaponFactory {
public:
    static WeaponType matchHeroWeapon(PlayableCharacter* hero);
    static Weapon* createWeapon(int posX, int posY, int strenght, WeaponType w, bool rare=false, bool legendary=false);

};


#endif //PROGETTO_PROGRAMMAZIONE_WEAPONFACTORY_H
