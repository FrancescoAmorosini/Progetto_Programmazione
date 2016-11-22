//
// Created by francesco amorosini on 22/11/16.
//

#include "HUD.h"

HUD::HUD(GameLevel *lvl) : subject(lvl->hero) {
    orbUsedText.setString("");
    heroWeapon= subject->getWeapon()->text;

    attach();
}

int HUD::getHP() const {
    return HP;
}

void HUD::setHP(int HP) {
    HUD::HP = HP;
}

int HUD::getEnemiesKilled() const {
    return enemiesKilled;
}

int HUD::getOrbUsed() const {
    return orbUsed;
}

int HUD::getChestOpened() const {
    return chestOpened;
}

int HUD::getHeartsPicked() const {
    return heartsPicked;
}


int HUD::getSpellshot() const {
    return spellshot;
}

void HUD::attach() {
    subject->registerObserver(this);
}

void HUD::detach() {
    if(subject) {
        subject->unregisterObserver(this);
        subject = nullptr;
    }
}

void HUD::update() {
    HP = subject->getHP();
    orbUsedText = subject->orbUsedText;
    heroWeapon = subject->getWeapon()->text;
    if(subject->enemykilled) {
        enemiesKilled ++;
        subject->enemykilled=false;
    }
    if(subject->orbUsed) {
        orbUsed ++;
        subject->orbUsed=false;
    }
    if(subject->chestOpened) {
        chestOpened++;
        subject->chestOpened = false;
    }
    if(subject->spellshot) {
        spellshot++;
        subject->spellshot = false;
    }
    if(subject->heartpicked) {
        heartsPicked++;
        subject->heartpicked = false;
    }
}