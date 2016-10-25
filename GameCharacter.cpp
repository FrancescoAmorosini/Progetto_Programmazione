//
// Created by Francesco Amorosini on 22/06/16.
//

#include "GameCharacter.h"

GameCharacter::GameCharacter(CharacterClass r, int HP, int atk, int evade, int critical) :
     role(r),  HP(HP), maxHP(HP), atk(atk), evade(evade), critical(critical){
}

int GameCharacter::getHP() const {
    return HP;
}

void GameCharacter::setmaxHP(int maxHP) {
    this->maxHP=maxHP;
}

int GameCharacter::getmaxHP() const {
    return maxHP;
}

void GameCharacter::setHP(int HP) {
    this->HP=HP;
    if(this->HP<0)
        this->HP=0;
    if(this->HP>maxHP)
        this->HP=maxHP;
}

int GameCharacter::getAtk() const {
    return atk;
}

void GameCharacter::setAtk(int atk) {
    this->atk=atk;
}

int GameCharacter::getEvade() const {
    return evade;
}

void GameCharacter::setEvade(int evade) {
    this->evade=evade;
}

int GameCharacter::getCritical() const {
    return critical;
}

void GameCharacter::setCritical(int critical) {
    this->critical=critical;
}

CharacterClass GameCharacter::getRole() const {
    return role;
}

void GameCharacter::heal(int HP){
    setHP(getHP()+HP);
}

