//
// Created by Francesco Amorosini on 22/06/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H

#include <string>
#include "RNG.h"


enum class CharacterClass {Warrior, Thief, Mage, Undead, BigBaldGuy, Witch, Bat};
enum class Face {Up, Down, Left, Right};

class GameCharacter {
public:
    GameCharacter(){}
    GameCharacter(CharacterClass r, int HP=100, int atk=10, int evade=1, int critical=1);
    virtual ~GameCharacter(){}

    virtual void updatePosition()=0;
    virtual void fight(GameCharacter* enemy)=0;

    int getHP() const;
    virtual void setHP(int HP);
    int getmaxHP() const;
    void setmaxHP(int maxHP);
    void heal(int HP);
    int getAtk() const;
    void setAtk(int atk);
    int getEvade() const;
    void setEvade(int evade);
    int getCritical() const;
    void setCritical(int critical);
    CharacterClass getRole() const;


    bool canMoveUP=true;
    bool canMoveDOWN=true;
    bool canMoveLEFT=true;
    bool canMoveRIGHT=true;

    int speedMovement=3;
    int walkingCounter=1;
    Face face= Face::Down;

private:
    int HP;
    int maxHP;
    int atk;
    int evade;
    int critical;
    CharacterClass role;
};



#endif //PROGETTO_PROGRAMMAZIONE_GAMECHARACTER_H
