//
// Created by Francesco Amorosini on 22/06/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_WEAPON_H
#define PROGETTO_PROGRAMMAZIONE_WEAPON_H

#include "DrawableObject.h"
#include "RNG.h"
#include "GameCharacter.h"

enum class WeaponType {Sword, Dagger, Staff};

class Weapon : public DrawableObject {
public:
    Weapon(float x, float y, int strenght, WeaponType w, bool rare=false, bool legendary=false);

    int useWeapon();

    int getStrenght() const;
    void setStrenght(int strenght);
    bool isRare() const;
    void setRare(bool rare);
    bool isLegendary() const;
    void setLegendary(bool legendary);
    WeaponType getWeapon() const;
    static WeaponType matchRole(GameCharacter* hero);

private:

    int strenght;
    WeaponType weapon;
    bool rare;
    bool legendary;
};


#endif //PROGETTO_PROGRAMMAZIONE_WEAPON_H
