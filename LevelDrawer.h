//
// Created by francesco amorosini on 27/10/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_LEVELDRAWER_H
#define PROGETTO_PROGRAMMAZIONE_LEVELDRAWER_H
#include "LevelCreator.h"

class LevelDrawer : public Observer {
public:
    LevelDrawer(GameLevel* lvl);

    void drawLevel(sf::RenderWindow *window);
    void drawHUD(sf::RenderWindow* window);
    void drawAchievement(sf::RenderWindow* window);
    void drawGameOver(sf::RenderWindow* window);
    int loadResources();

    void attach() override;
    void detach() override;
    void update() override;

private:
    sf::View playerview;
    sf::Texture HUD;
    sf::Texture achievements;
    sf::Texture gameOverSplash;
    sf::Sprite emptyBar;
    sf::Sprite hpBar;
    sf::Sprite frame;
    sf::Sprite medal;
    sf::Text heroWeapon;
    sf::Text HPtext;
    sf::Text achievementText;

    sf::Music BGM;


    int killedTime=0;
    int chestTime=0;
    int orbTime=0;
    int heartTime=0;
    int spellTime=0;
    int orbTextPos=0;

    int HP;
    int enemiesKilled=0;
    int orbUsed=0;
    int chestOpened=0;
    int heartsPicked=0;
    int spellshot=0;
    sf::Text orbUsedText;
    bool gameover;

    GameLevel* level;

    PlayableCharacter* subject;
};

#endif //PROGETTO_PROGRAMMAZIONE_LEVELDRAWER_H
