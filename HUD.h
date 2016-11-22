//
// Created by francesco amorosini on 22/11/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_HUD_H
#define PROGETTO_PROGRAMMAZIONE_HUD_H


#include <SFML/Graphics/Text.hpp>
#include "Observer.h"
#include "PlayableCharacter.h"
#include "GameLevel.h"

class HUD : public Observer {
public:
    HUD(GameLevel* lvl);

    void attach() override;
    void detach() override;
    void update() override;

    int getHP() const;
    void setHP(int HP);
    int getEnemiesKilled() const;
    int getOrbUsed() const;
    int getChestOpened() const;
    int getHeartsPicked() const;
    int getSpellshot() const;

    int killedTime=0;
    int chestTime=0;
    int orbTime=0;
    int heartTime=0;
    int spellTime=0;
    int orbTextPos=0;

    sf::Text orbUsedText;
    sf::Text heroWeapon;

private:

    int HP;
    int enemiesKilled=0;
    int orbUsed=0;
    int chestOpened=0;
    int heartsPicked=0;
    int spellshot=0;

    PlayableCharacter* subject;
};


#endif //PROGETTO_PROGRAMMAZIONE_HUD_H
