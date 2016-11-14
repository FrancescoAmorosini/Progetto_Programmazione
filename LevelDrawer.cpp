//
// Created by Francesco Amorosini on 19/10/16.
//

#include "LevelDrawer.h"

LevelDrawer::LevelDrawer(GameLevel *lvl) : subject(lvl){
    //Sets View
    sf::View view(sf::FloatRect(200, 200, 300, 200));
    playerview = view;

    //Loads Resources
    if(loadResources() == EXIT_FAILURE)
        throw std::runtime_error("Error: Cannot open file");

    attach();
}

void LevelDrawer::drawLevel( sf::RenderWindow* window){
    playerview.setSize(sf::Vector2f(window->getSize().x/2, window->getSize().y/2));

    //Draws Map and Walls
    for(int i=0; i<subject->map->buffer.size(); i++) {
            window->draw(subject->map->buffer[i]->sprite);
    }
    for(int i=0; i< subject->map->wallBuffer.size(); i++)
        window->draw(subject->map->wallBuffer[i]->sprite);

    //Draws Orbs
    for(int i=0; i< subject->orbs.size(); i++)
        window->draw(subject->orbs[i]->sprite);

    //Draws Spells
    for(int i=0; i< subject->spells.size(); i++){
        subject->spells[i]->sprite.setTexture(subject->fireballTexture);
        window->draw(subject->spells[i]->sprite);
    }
    for(int i=0; i< subject->enemySpells.size(); i++) {
        subject->enemySpells[i]->sprite.setTexture(subject->fireballTexture);
        window->draw(subject->enemySpells[i]->sprite);
    }
    //Draws Hero
    window->draw(subject->hero->sprite);
    window->draw(subject->hero->text);

    //Draws Enemies
    for(int i=0; i< subject->enemies.size(); i++){
        window->draw(subject->enemies[i]->sprite);
        window->draw(subject->enemies[i]->text);
    }
    //Draws Chests
    for(int i=0; i< subject->chests.size(); i++){
        window->draw(subject->chests[i]->sprite);
        window->draw(subject->chests[i]->text);
    }
    //Draws Hearts
    for(int i=0; i< subject->hearts.size(); i++){
        window->draw(subject->hearts[i]->sprite);
    }
    //Draws Weapon
    for(int i=0; i< subject->weapons.size(); i++) {
        subject->weapons[i]->sprite.setTexture(subject->weaponTexture);
        window->draw(subject->weapons[i]->sprite);
        subject->weapons[i]->text.setFont(subject->healthFont);
        window->draw(subject->weapons[i]->text);
    }

    window->setView(playerview);
    playerview.setCenter(subject->hero->rect.getPosition());

    drawHUD(window);
}

void LevelDrawer::drawHUD(sf::RenderWindow *window) {
    int filledBar = subject->hero->getHP() * 100 /subject->hero->getmaxHP();
    emptyBar.setPosition(playerview.getCenter().x - 50, 220 + playerview.getCenter().y);
    hpBar.setPosition(emptyBar.getPosition().x + 2, emptyBar.getPosition().y + 2);
    hpBar.setTextureRect(sf::IntRect(0,0,filledBar,12));
    hptext.setPosition(emptyBar.getPosition().x - 40, emptyBar.getPosition().y - 5);
    window->draw(hptext);
    window->draw(emptyBar);
    window->draw(hpBar);
}

int LevelDrawer::loadResources() {
    //Load HUD
    if(!HUD.loadFromFile("Resources/EmptyBar.png"))
        return EXIT_FAILURE;
    emptyBar.setTextureRect(sf::IntRect(0,16,106,16));
    emptyBar.setTexture(HUD);
    //Load HPBar
    if(!Bar.loadFromFile("Resources/HPBar.png"))
        return EXIT_FAILURE;
    hpBar.setTexture(Bar);
    //Sets HPtext
    hptext.setFont(subject->healthFont);
    hptext.setString("HP ");
    hptext.setCharacterSize(20);

    return EXIT_SUCCESS;
}

void LevelDrawer::attach() {
    subject->registerObserver(this);
}

void LevelDrawer::detach() {
    subject->unregisterObserver(this);
}

void LevelDrawer::update() {
    HP = subject->hero->getHP();
    enemiesKilled= subject->enemiesKilled;
    wallsBroken= subject->wallsBroken;
    chestOpened= subject->chestOpened;
}
