//
// Created by Francesco Amorosini on 26/06/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_CHEST_H
#define PROGETTO_PROGRAMMAZIONE_CHEST_H

#include "Orb.h"
#include "Weapon.h"
#include "PlayableCharacter.h"
#include "DrawableObject.h"


class Chest : public DrawableObject {
public:
    Chest(float posX, float posY, Weapon* w);
    Chest(float posX, float posY, Orb* o);

    virtual ~Chest();

    void openChest(PlayableCharacter* hero);

    Weapon* getWeapon() const;
    void setWeapon(Weapon *weapon);
    Orb* getOrb() const;
    void setOrb(Orb *orb);

    static sf::Clock objectTaken;
    static sf::Time  delay;

private:
    Weapon* weapon;
    Orb* orb;

};


#endif //PROGETTO_PROGRAMMAZIONE_CHEST_H
