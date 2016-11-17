//
// Created by Francesco Amorosini on 22/07/16.
//

#include "GameLevel.h"

GameLevel::GameLevel(Map* map, PlayableCharacter* hero, std::vector<Chest*> chests,
                     std::vector<Orb*> orbs, std::vector<Enemy*> enemies, std::vector<Heart*> hearts)
        : map(map),hero(hero), chests(chests),orbs(orbs), enemies(enemies), hearts(hearts){

}

void GameLevel::updateLevel() {
    int chestIndex = 0;
    int wallIndex = 0;
    int enemyIndex = 0;
    bool isThief = false;
    //DASH IF THIEF
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && hero->getRole() == CharacterClass::Thief)
        isThief = true;
    restart:
    //MOVE UP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        hero->face = Face::Up;
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {         // avoids collisions
            hero->rect.move(0, -hero->speedMovement);
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //MOVE DOWN
        hero->face = Face::Down;
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {
            hero->rect.move(0, hero->speedMovement);
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        //MOVE LEFT
        hero->face = Face::Left;
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {
            hero->rect.move(-hero->speedMovement, 0);
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //MOVE RIGHT
        hero->face = Face::Right;
        hero->sprite.setTextureRect(sf::IntRect(hero->walkingCounter * 32, 32 * 2, 32, 32));
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {
            hero->rect.move(hero->speedMovement, 0);
        }

    }
    hero->updateDirection();
    //MOVES TWICE IF THIEF
    if (isThief) {
        isThief=false;
        goto restart;
    }
    //ACTION BUTTON
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        //Start fighting animation;
        hero->isFighting=true;
        //BREAKS WALL IF BREAKABLE
        if (checkWallCollision(hero->rect, hero->face, &wallIndex) && map->wallBuffer[wallIndex]->breakable) {
            map->wallBuffer.erase(map->wallBuffer.begin() + wallIndex);
            map->wallBroken=true;
        }
            //OPENS CHEST
        else if (checkChestCollision(hero->rect, hero->face, &chestIndex)) {
            if (Chest::objectTaken.getElapsedTime() >= Chest::delay) {
                chests[chestIndex]->openChest(hero);
                chestOpened=true;
                Chest::objectTaken.restart();
            }
        }
            //SHOOTS FIREBALL IF MAGE
        else if (hero->getRole() == CharacterClass::Mage &&
                 Spell::projectileLife.getElapsedTime() >= Spell::projectileLifeSpan) {    //Avoids Spammed Spells
            Spell *spell = new Spell(
                    hero->rect.getPosition().x + hero->rect.getSize().x / 2 - 13,    //13= Half Spell Sprite
                    hero->rect.getPosition().y + hero->rect.getSize().y / 2 - hero->rect.getSize().y / 2,
                    hero->face);
            spells.push_back(spell);
            Spell::projectileLife.restart();
            spellshot=true;
        } else {
            //PHYSICAL ATTACK IF NOT MAGE
            if (checkCloseEnemy(hero->rect, hero->face, &enemyIndex) &&
                hero->hitRate.getElapsedTime().asSeconds() > 0.4) {
                hero->fight(enemies[enemyIndex]);
                enemies[enemyIndex]->aggroed = true;
                if (enemies[enemyIndex]->getHP() == 0) {
                    if (RNG::throwCoin(Enemy::dropChance))
                        weapons.push_back(enemies[enemyIndex]->dropWeapon());
                    enemies.erase(enemies.begin() + enemyIndex);
                    hero->enemyKilled=true;
                }
                hero->hitRate.restart();
            }
        }
    }
    // USE ORB
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
       for(int i=0; i<10; i++){
           if(hero->getInventory(i) && Orb::usedOrb.getElapsedTime() > sf::seconds(0.5)){
               hero->getInventory(i)->useOrb(hero);
               hero->inventory.erase(hero->inventory.begin() +i);
               Orb::usedOrb.restart();
               break;
           }
       }
    }

        //Update hero sprite
    hero->updatePosition();
    checkOrbsCollisions();      //picks up orbs
    checkHeartsCollisions();   //picks up hearts
    checkWeaponsCollisions();  // picks up weapons
    checkEnemiesCollisions(); //gets damaged
    if(hero->getHP() == 0)
        gameover=true;

    //Manages enemies
    for (int i = 0; i < enemies.size(); i++) {
        //Turns in a random direction or hero direction if aggroed
        bool bat= false;
        if(enemies[i]->getRole() == CharacterClass::Bat)
            bat=true;
        bat:
        enemies[i]->turnAround(hero);
        //Checks if enemy can move in that direction
        if (!checkWallCollision(enemies[i]->rect, enemies[i]->face, &wallIndex) &&
            !checkChestCollision(enemies[i]->rect, enemies[i]->face, &chestIndex))
            enemies[i]->move();
        //Doubles speed if bat
        if(bat) {
            bat = false;
            goto bat;
        }
        //Shoots a spell if enough time is passed since last shot
        if (Spell::enemyProjectileLife.getElapsedTime() > Spell::projectileLifeSpan) {
            Spell* spell = enemies[i]->shootSpell();
            // checks if spell a void pointer
            if(spell) {
                enemySpells.push_back(spell);
                Spell::enemyProjectileLife.restart();
            }
        }
    }

    //Manages projectiles
    for (int i = 0; i < spells.size(); i++) {
        spells[i]->updateSpell();
        //Ereases spells
        if (spells[i]->projectileLife.getElapsedTime().asSeconds() > 2 || checkProjectileCollisions(spells[i]))
            spells.erase(spells.begin() + i);
        //checks if hits an enemy
        checkProjectileHit(spells[i], &i);

    }
    for (int i = 0; i < enemySpells.size(); i++) {
        enemySpells[i]->updateSpell();
        if (enemySpells[i]->enemyProjectileLife.getElapsedTime().asSeconds() > 2 ||
            checkProjectileCollisions(enemySpells[i]))
            enemySpells.erase(enemySpells.begin() + i);
        else if (enemySpells[i]->rect.getGlobalBounds().intersects(hero->rect.getGlobalBounds())) {
            enemySpells.erase(enemySpells.begin() + i);
            hero->setHP(hero->getHP() - 5);                           //Spells makes 10 HP damage
        }
    }

    notify();
}

bool GameLevel::checkProjectileCollisions(Spell* spell) {
    for (int i = 0; i < chests.size(); i++) {
        if (spell->rect.getGlobalBounds().intersects(chests[i]->rect.getGlobalBounds())) {
            return true;
        }
    }

    for (int i = 0; i < map->wallBuffer.size(); i++) {
        if (spell->rect.getGlobalBounds().intersects(map->wallBuffer[i]->rect.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

void GameLevel::checkProjectileHit(Spell *spell, int *index) {
    for (int i = 0; i < enemies.size(); i++) {
        if (spell->rect.getGlobalBounds().intersects(enemies[i]->rect.getGlobalBounds())) {
            spells.erase(spells.begin() + *index);
            hero->fight(enemies[i]);
            enemies[i]->aggroed = true;
            if (enemies[i]->getHP() == 0) {
                if (RNG::throwCoin(Enemy::dropChance))
                    weapons.push_back(enemies[i]->dropWeapon());
                enemies.erase(enemies.begin() + i);
                hero->enemyKilled=true;
            }
            break;
        }
    }
}

void GameLevel::checkOrbsCollisions() {
    for (int i = 0; i < orbs.size(); i++) {
        if (hero->rect.getGlobalBounds().intersects(orbs[i]->rect.getGlobalBounds()))
        {
            hero->setInventory(orbs[i]);
            orbs.erase(orbs.begin() + i);
            break;
        }
    }
}

void GameLevel::checkHeartsCollisions(){
        for (int i = 0; i < hearts.size(); i++)
            if (hero->rect.getGlobalBounds().intersects(hearts[i]->rect.getGlobalBounds()))
            {
                hearts[i]->restoreHealth(hero);
                hearts.erase(hearts.begin() + i);
                heartpicked=true;
                break;
            }
    }

void GameLevel::checkWeaponsCollisions() {
    for (int i = 0; i < weapons.size(); i++) {
        if (hero->rect.getGlobalBounds().intersects(weapons[i]->rect.getGlobalBounds()))
        {
            hero->setWeapon(weapons[i]);
            weapons.erase(weapons.begin() + i);
            break;
        }
    }
}

void GameLevel::checkEnemiesCollisions() {
    for (int i = 0; i < enemies.size(); i++) {
        if (hero->rect.getGlobalBounds().intersects(enemies[i]->rect.getGlobalBounds()) &&
            hero->damageRate.getElapsedTime().asSeconds() > 0.8) {
            enemies[i]->fight(hero);
            hero->damageRate.restart();
        }
    }
}

bool GameLevel::checkChestCollision(sf::RectangleShape rect, const Face face, int* index) {
    int toll = 2;
    for (int i = 0; i < chests.size(); i++) {
        switch (face) {
            case Face::Up:
                if (abs(static_cast<int>(chests[i]->rect.getPosition().y + 32 - rect.getPosition().y)) < toll &&
                    abs(static_cast<int>(chests[i]->rect.getPosition().x - rect.getPosition().x)) < 32 - toll) {
                    *index = i;
                    return true;
                }
                break;
            case Face::Down:
                if (abs(static_cast<int>(chests[i]->rect.getPosition().y - rect.getPosition().y )) < 32 &&
                    abs(static_cast<int>(chests[i]->rect.getPosition().x - rect.getPosition().x)) < 32 - toll) {
                    *index = i;
                    return true;
                }
                break;
            case Face::Left:
                if (abs(static_cast<int>(chests[i]->rect.getPosition().y - rect.getPosition().y )) < 32 - toll &&
                    abs(static_cast<int>(chests[i]->rect.getPosition().x + 32 - rect.getPosition().x)) < toll) {
                    *index = i;
                    return true;
                }
                break;
            case Face::Right:
                if (abs(static_cast<int>(chests[i]->rect.getPosition().y - rect.getPosition().y )) < 32 - toll &&
                    abs(static_cast<int>(chests[i]->rect.getPosition().x - 32 - rect.getPosition().x)) < toll) {
                    *index = i;
                    return true;
                }
                break;
        }
    }
    return false;
}

bool GameLevel::checkWallCollision(sf::RectangleShape rect,Face face, int *index) {
    int toll = 2;
    for (int i = 0; i < map->wallBuffer.size(); i++) {
        if (!map->wallBuffer[i]->isWalkable()) {
            switch (face) {
                case Face::Up:
                    if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y + 32 - rect.getPosition().y)) <
                        toll &&
                        abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x - rect.getPosition().x)) <
                        32 - toll) {
                        *index = i;
                        return true;
                    }
                    break;
                case Face::Down:
                    if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y - 32 - rect.getPosition().y )) <
                        toll &&
                        abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x - rect.getPosition().x)) <
                        32 - toll) {
                        *index = i;
                        return true;
                    }
                    break;
                case Face::Left:
                    if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y - rect.getPosition().y )) <
                        32 - toll &&
                        abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x + 32 - rect.getPosition().x)) <
                        toll) {
                        *index = i;
                        return true;
                    }
                    break;
                case Face::Right:
                    if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y - rect.getPosition().y )) <
                        32 - toll &&
                        abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x - 32 - rect.getPosition().x)) <
                        toll) {
                        *index = i;
                        return true;
                    }
                    break;
            }
        }
    }
    return false;
}

bool GameLevel::checkCloseEnemy(sf::RectangleShape rect, Face face, int *index) {
    for (int i = 0; i < enemies.size(); i++) {
        switch (face) {
            //ADJUST HITBOX
            case Face::Up:
                rect.setSize(sf::Vector2f(32, 48));
                rect.move(0,-20);
                break;
            case Face::Down:
                rect.setSize(sf::Vector2f(32, 48));
                rect.move(0,15);
            case Face::Left:
                rect.setSize(sf::Vector2f(48, 32));
                rect.move(-10,0);
                break;
            case Face::Right:
                rect.setSize(sf::Vector2f(48, 32));
                rect.move(-15,0);
                break;
        }
        if (rect.getGlobalBounds().intersects(enemies[i]->rect.getGlobalBounds())){
            *index=i;
            return true;
        }
    }
    return false;
}

void GameLevel::registerObserver(Observer *O) {
    observers.push_back(O);
}

void GameLevel::unregisterObserver(Observer *O) {
    observers.remove(O);
}

void GameLevel::notify() const {
    for (auto itr = std::begin(observers); itr != std::end(observers); itr++){
        (*itr)->update();
    }
}