//
// Created by francesco amorosini on 27/10/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_LEVELDRAWER_H
#define PROGETTO_PROGRAMMAZIONE_LEVELDRAWER_H

#include "LevelCreator.h"
#include "HUD.h"

class LevelDrawer {
public:
    LevelDrawer(GameLevel* lvl);
    virtual ~LevelDrawer(){
        delete data;
    }

    void drawLevel(sf::RenderWindow *window);
    void drawHUD(sf::RenderWindow* window);
    void drawAchievement(sf::RenderWindow* window);
    void drawGameOver(sf::RenderWindow* window);
    int loadResources();

private:
    sf::View playerview;
    sf::Texture hud;
    sf::Texture achievements;
    sf::Texture gameOverSplash;
    sf::Sprite emptyBar;
    sf::Sprite hpBar;
    sf::Sprite frame;
    sf::Sprite medal;
    sf::Text HPtext;
    sf::Text achievementText;

    sf::Music BGM;


    GameLevel* level;
    HUD* data;
};

#endif //PROGETTO_PROGRAMMAZIONE_LEVELDRAWER_H
