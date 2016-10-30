//
// Created by Francesco Amorosini on 22/06/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H

#ifndef Included_RangeException_H
#define Included_RangeException_H
#include "RangeException.h"

#endif

#include "GameCharacter.h"
#include "Weapon.h"
#include <vector>

class Orb;

class PlayableCharacter: public GameCharacter, public DrawableObject {
public:
    PlayableCharacter(float x, float y,CharacterClass r, std::string name, Weapon* w, int HP=100, int atk=10, int evade=1, int critical=1) throw(std::invalid_argument);
    virtual ~PlayableCharacter();

    virtual void updatePosition() override;
    virtual void fight(GameCharacter* enemy) override;
    virtual void setHP(int HP) override;
    void updateDirection();

    const std::string getName() const;
    void setName(const std::string &name);
    Weapon *getWeapon() const;
    void setWeapon(Weapon* weapon);
    const Orb* getInventory(int index) const throw(RangeException);
    void setInventory(Orb* o);

    sf::Clock damageRate;
    sf::Clock hitRate;
    bool isFighting = false;

private:
    std::string name;
    Weapon* weapon;
    std::vector<Orb*> inventory;
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
