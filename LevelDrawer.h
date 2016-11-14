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
    int loadResources();

    void attach() override;
    void detach() override;
    void update() override;

private:
    sf::View playerview;
    sf::Texture HUD;
    sf::Texture Bar;
    sf::Text hptext;
    sf::Sprite emptyBar;
    sf::Sprite hpBar;
    sf::Sprite frames;

    int HP;
    int enemiesKilled;
    int wallsBroken;
    int chestOpened;

    GameLevel* subject;
};

#endif //PROGETTO_PROGRAMMAZIONE_LEVELDRAWER_H
