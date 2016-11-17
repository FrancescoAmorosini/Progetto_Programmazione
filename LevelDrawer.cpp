//
// Created by Francesco Amorosini on 19/10/16.
//

#include <iostream>
#include "LevelDrawer.h"

LevelDrawer::LevelDrawer(GameLevel *lvl) : subject(lvl){
    //Sets View
    sf::View view(sf::FloatRect(200, 200, 300, 200));
    playerview = view;

    //Loads Resources
    if(loadResources() == EXIT_FAILURE)
        throw std::runtime_error("Error: Cannot open file");
    BGM.play();

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
    drawAchievement(window);
    drawHUD(window);

    playerview.setCenter(subject->hero->rect.getPosition());


}

void LevelDrawer::drawHUD(sf::RenderWindow *window) {
    int filledBar = subject->hero->getHP() * 100 / subject->hero->getmaxHP();

    emptyBar.setPosition(playerview.getCenter().x - 200, 220 + playerview.getCenter().y);
    hpBar.setPosition(emptyBar.getPosition().x + 2, emptyBar.getPosition().y + 2);
    hpBar.setTextureRect(sf::IntRect(0, 0, filledBar, 12));
    HPtext.setPosition(emptyBar.getPosition().x - 40, emptyBar.getPosition().y - 5);
    achievementText.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y-250);

    for (int i = 0; i < 10; i++) {
        frame.setPosition((emptyBar.getPosition().x + 300) + i * 32, emptyBar.getPosition().y);
        if(subject->hero->getInventory(i)){
            Orb o(frame.getPosition().x + 5, frame.getPosition().y +5,subject->hero->getInventory(i)->getOrbColor());
            o.sprite.setTexture(subject->orbTexture);
            window->draw(o.sprite);
        }
        window->draw(frame);
    }
    //Bronze medal
    if(enemiesKilled>=3) {
        medal.setTextureRect(sf::IntRect(0, 0, 13, 26));
        medal.setPosition(achievementText.getPosition().x + 200,achievementText.getPosition().y);
        window->draw(medal);
    }
    //Silver medal
    if(enemiesKilled>=5) {
        medal.setTextureRect(sf::IntRect(13, 0, 13, 26));
        medal.setPosition(achievementText.getPosition().x + 225,achievementText.getPosition().y);
        window->draw(medal);
    }
    //Golden medal
    if(enemiesKilled>=10) {
        medal.setTextureRect(sf::IntRect(26, 0, 13, 26));
        medal.setPosition(achievementText.getPosition().x + 250,achievementText.getPosition().y);
        window->draw(medal);
    }
    //Chest medal
    if(chestOpened>=3) {
        medal.setTextureRect(sf::IntRect(60, 0, 13, 26));
        medal.setPosition(achievementText.getPosition().x + 275,achievementText.getPosition().y);
        window->draw(medal);
    }//Wall medal
    if(wallsBroken>=2) {
        medal.setTextureRect(sf::IntRect(73, 0, 26, 26));
        medal.setPosition(achievementText.getPosition().x + 300,achievementText.getPosition().y);
        window->draw(medal);
    }//Heart medal
    if(heartsPicked>=3) {
        medal.setTextureRect(sf::IntRect(43, 0, 13, 26));
        medal.setPosition(achievementText.getPosition().x + 350,achievementText.getPosition().y);
        window->draw(medal);
    }//Spell medal
    if(spellshot >= 10) {
        medal.setTextureRect(sf::IntRect(102, 0, 26, 26));
        medal.setPosition(achievementText.getPosition().x + 375,achievementText.getPosition().y);
        window->draw(medal);
    }

    window->draw(achievementText);
    window->draw(HPtext);
    window->draw(emptyBar);
    window->draw(hpBar);
}
void LevelDrawer::drawAchievement(sf::RenderWindow *window) {
    //3 ENEMIES KILLED
    if (enemiesKilled >= 3 && killedTime < 200) {
        sf::Text bronzekill;
        bronzekill.setFont(subject->healthFont);
        bronzekill.setString("Achievement unlocked : 3 enemies killed! ");
        bronzekill.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y - 220);
        medal.setPosition(playerview.getCenter().x + 100, playerview.getCenter().y - 220);
        medal.setTextureRect(sf::IntRect(0, 0, 13, 26));
        bronzekill.setCharacterSize(20);
        window->draw(bronzekill);
        window->draw(medal);
        killedTime++;
    }//5 ENEMIES KILLED
    else if (enemiesKilled >= 5 && killedTime < 400) {
        sf::Text silverkill;
        silverkill.setFont(subject->healthFont);
        silverkill.setString("Achievement unlocked : 5 enemies killed! ");
        silverkill.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y - 220);
        medal.setPosition(playerview.getCenter().x + 100, playerview.getCenter().y - 220);
        medal.setTextureRect(sf::IntRect(13, 0, 13, 26));
        silverkill.setCharacterSize(20);
        window->draw(silverkill);
        window->draw(medal);
        killedTime++;
    }// 10ENEMIES KILLED
    else if (enemiesKilled >= 10 && killedTime < 600) {
        sf::Text goldenkill;
        goldenkill.setFont(subject->healthFont);
        goldenkill.setString("Achievement unlocked : 10 enemies killed! ");
        goldenkill.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y - 220);
        medal.setPosition(playerview.getCenter().x + 100, playerview.getCenter().y - 220);
        medal.setTextureRect(sf::IntRect(26, 0, 13, 26));
        goldenkill.setCharacterSize(20);
        window->draw(goldenkill);
        window->draw(medal);
        killedTime++;
    }//3 CHESTS OPENED
    else if (chestOpened >= 3 && chestTime < 200) {
        sf::Text chestopen;
        chestopen.setFont(subject->healthFont);
        chestopen.setString("Achievement unlocked : 3 chest opened! ");
        chestopen.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y - 220);
        medal.setPosition(playerview.getCenter().x + 100, playerview.getCenter().y - 220);
        medal.setTextureRect(sf::IntRect(60, 0, 13, 26));
        chestopen.setCharacterSize(20);
        window->draw(chestopen);
        window->draw(medal);
        chestTime++;
    }//2 WALLS BROKEN
    else if (wallsBroken >= 2 && wallTime < 200) {
        sf::Text chestopen;
        chestopen.setFont(subject->healthFont);
        chestopen.setString("Achievement unlocked : 2 walls broken! ");
        chestopen.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y - 220);
        medal.setPosition(playerview.getCenter().x + 100, playerview.getCenter().y - 220);
        medal.setTextureRect(sf::IntRect(73, 0, 26, 26));
        chestopen.setCharacterSize(20);
        window->draw(chestopen);
        window->draw(medal);
        wallTime++;
    }//3 HEARTS PICKED UP
    else if (heartsPicked >= 3 && heartTime < 200) {
        sf::Text heartpicked;
        heartpicked.setFont(subject->healthFont);
        heartpicked.setString("Achievement unlocked : 3 hearts picked! ");
        heartpicked.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y - 220);
        medal.setPosition(playerview.getCenter().x + 100, playerview.getCenter().y - 220);
        medal.setTextureRect(sf::IntRect(43, 0, 13, 26));
        heartpicked.setCharacterSize(20);
        window->draw(heartpicked);
        window->draw(medal);
        heartTime++;
    }
    else if (spellshot >= 10 && spellTime < 200) {
        sf::Text spelltext;
        spelltext.setFont(subject->healthFont);
        spelltext.setString("Achievement unlocked : 10 spells shot! ");
        spelltext.setPosition(playerview.getCenter().x - 450, playerview.getCenter().y - 220);
        medal.setPosition(playerview.getCenter().x + 100, playerview.getCenter().y - 220);
        medal.setTextureRect(sf::IntRect(102, 0, 26, 26));
        spelltext.setCharacterSize(20);
        window->draw(spelltext);
        window->draw(medal);
        spellTime++;
    }
}

int LevelDrawer::loadResources() {
    //Music
    if(!BGM.openFromFile("Resources/BGM.ogg"))
        return EXIT_FAILURE;
    BGM.setLoop(true);

    //Load HUD
    if(!HUD.loadFromFile("Resources/HUD.png"))
        return EXIT_FAILURE;
    emptyBar.setTextureRect(sf::IntRect(0,16,106,16));
    emptyBar.setTexture(HUD);
    hpBar.setTextureRect(sf::IntRect(0,0,106,13));
    hpBar.setTexture(HUD);
    frame.setTextureRect(sf::IntRect(106,1,32,32));
    frame.setTexture(HUD);
    //Load Achievements
    if(!achievements.loadFromFile("Resources/Achievements.png"))
        return EXIT_FAILURE;
    medal.setTexture(achievements);
    if(!gameOverSplash.loadFromFile("Resources/gameover.jpg"))
        return EXIT_FAILURE;
    //Sets Text
    HPtext.setFont(subject->healthFont);
    HPtext.setString("HP ");
    HPtext.setCharacterSize(20);
    achievementText.setFont(subject->healthFont);
    achievementText.setString("Achievements :");
    achievementText.setCharacterSize(20);

    return EXIT_SUCCESS;
}
void LevelDrawer::drawGameOver(sf::RenderWindow *window) {
    detach();
    playerview.setCenter(0,0);
    window->setView(playerview);
    sf::Sprite gameover;
    gameover.setPosition(-430,-300);
    gameover.setTexture(gameOverSplash);
    window->draw(gameover);
    BGM.stop();
}

void LevelDrawer::attach() {
    subject->registerObserver(this);
}

void LevelDrawer::detach() {
    if(subject) {
        subject->unregisterObserver(this);
        subject = nullptr;
    }
}

void LevelDrawer::update() {
    HP = subject->hero->getHP();
    if(subject->hero->enemyKilled) {
        enemiesKilled ++;
        subject->hero->enemyKilled=false;
    }
    if(subject->map->wallBroken) {
        wallsBroken ++;
        subject->map->wallBroken=false;
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

    gameover=subject->gameover;
}
