//
// Created by Francesco Amorosini on 22/07/16.
//

#include "GameLevel.h"

GameLevel::GameLevel(Map* map, PlayableCharacter* hero, std::vector<Chest*> chests,
                     std::vector<Orb*> orbs, std::vector<Enemy*> enemies, std::vector<Heart*> hearts)
        : map(map),hero(hero), chests(chests),orbs(orbs), enemies(enemies), hearts(hearts){

}

void GameLevel::updateLevel() {
    int speed = hero->speedMovement;
    int chestIndex = 0;
    int wallIndex = 0;
    int enemyIndex = 0;
    //DASH
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && hero->getRole() == CharacterClass::Thief)
        speed = speed * 2;
    //MOVE UP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        hero->face = Face::Up;
        hero->sprite.setTextureRect(sf::IntRect(hero->walkingCounter * 32, 32 * 3, 32, 32));
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {         // evita le collisioni
            hero->rect.move(0, -speed);
            hero->walkingCounter++;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //MOVE DOWN
        hero->sprite.setTextureRect(sf::IntRect(hero->walkingCounter * 32, 0, 32, 32));
        hero->face = Face::Down;
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {
            hero->rect.move(0, speed);
            hero->walkingCounter++;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        //MOVE LEFT
        hero->face = Face::Left;
        hero->sprite.setTextureRect(sf::IntRect(hero->walkingCounter * 32, 32 * 1, 32, 32));
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {
            hero->rect.move(-speed, 0);
            hero->walkingCounter++;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //MOVE RIGHT
        hero->face = Face::Right;
        hero->sprite.setTextureRect(sf::IntRect(hero->walkingCounter * 32, 32 * 2, 32, 32));
        if (!checkChestCollision(hero->rect, hero->face, &chestIndex) &&
            !checkWallCollision(hero->rect, hero->face, &wallIndex)) {
            hero->rect.move(speed, 0);
            hero->walkingCounter++;
        }

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        //BREAKS WALL IF BREAKABLE
        if (checkWallCollision(hero->rect, hero->face, &wallIndex) && map->wallBuffer[wallIndex]->breakable)
            map->wallBuffer.erase(map->wallBuffer.begin() + wallIndex);
            //OPENS CHEST
        else if (checkChestCollision(hero->rect, hero->face, &chestIndex)) {
            if (Chest::objectTaken.getElapsedTime() >= Chest::delay) {
                chests[chestIndex]->openChest(hero);
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
        } else {
            //PHYSICAL ATTACK IF NOT MAGE
            if (checkCloseEnemy(hero->rect, hero->face, &enemyIndex)) {
                hero->fight(enemies[enemyIndex]);
                if (enemies[enemyIndex]->getHP() == 0) {
                    if (RNG::throwCoin(Enemy::dropChance))
                        weapons.push_back(enemies[enemyIndex]->dropWeapon(matchRole()));
                    enemies.erase(enemies.begin() + enemyIndex);
                }
            }
        }
    }
    //Update hero sprite
    hero->updatePosition();
    if (hero->walkingCounter == 2)
        hero->walkingCounter = 0;
    checkOrbsCollisions();      //picks up orbs
    checkHeartsCollisions();   //picks up hearts
    checkWeaponsCollisions();  // picks up weapons
    checkEnemiesCollisions(); //gets damaged

    //Manages enemies
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->walkingTime.getElapsedTime().asSeconds() >= 0.5) {
            enemies[i]->face = static_cast<Face>(RNG::throwDice(11) -
                                                 1);   // 4/10 chance of moving in a random direction
            enemies[i]->walkingTime.restart();
        }
        if (!checkWallCollision(enemies[i]->rect, enemies[i]->face, &wallIndex) &&
            !checkChestCollision(enemies[i]->rect, enemies[i]->face, &chestIndex))
            enemies[i]->updatePosition();
    }

    //Manages projectiles
    for (int i = 0; i < spells.size(); i++) {
        spells[i]->updateSpell();
        checkProjectileCollisions(spells[i], &i);                                           //checks collisions with enemies
        if (checkChestCollision(spells[i]->rect, spells[i]->face, &chestIndex) ||         //checks colllisions with chests
            checkWallCollision(spells[i]->rect, spells[i]->face, &wallIndex))          //checks collisions with walls
            spells.erase(spells.begin() + i);
        if (spells[i]->projectileLife.getElapsedTime().asSeconds() > 1)                           //erases spells far enough
            spells.erase(spells.begin() + i);
    }
}

void GameLevel::checkProjectileCollisions(Spell* spell, int* index) {
    for (int i = 0; i < enemies.size(); i++) {
        if (spell->rect.getGlobalBounds().intersects(enemies[i]->rect.getGlobalBounds()))
        {
            spells.erase(spells.begin() + *index);
            hero->fight(enemies[i]);
            if(enemies[i]->getHP() == 0) {
                if(RNG::throwCoin(Enemy::dropChance))
                    weapons.push_back(enemies[i]->dropWeapon(matchRole()));
                enemies.erase(enemies.begin() + i);
            }
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
            hero->damageTimer.getElapsedTime().asSeconds() > 0.8) {
            enemies[i]->fight(hero);
            hero->damageTimer.restart();
        }
    }
}

bool GameLevel::checkChestCollision(sf::RectangleShape rect, Face face, int* index) {
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
    int toll=2;
    for (int i = 0; i < map->wallBuffer.size(); i++) {
        switch (face) {
            case Face::Up:
                if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y + 32 - rect.getPosition().y)) < toll &&
                    abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x - rect.getPosition().x)) < 32 - toll) {
                    *index = i;
                    return true;
                }
                break;
            case Face::Down:
                if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y - 32 - rect.getPosition().y )) < toll &&
                    abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x - rect.getPosition().x)) < 32 - toll) {
                    *index = i;
                    return true;
                }
                break;
            case Face::Left:
                if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y - rect.getPosition().y )) < 32 - toll &&
                    abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x + 32 - rect.getPosition().x)) < toll) {
                    *index = i;
                    return true;
                }
                break;
            case Face::Right:
                if (abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().y - rect.getPosition().y )) < 32 - toll &&
                    abs(static_cast<int>(map->wallBuffer[i]->rect.getPosition().x - 32 - rect.getPosition().x)) < toll) {
                    *index = i;
                    return true;
                }
                break;
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
                rect.move(0,-10);
                break;
            case Face::Down:
                rect.setSize(sf::Vector2f(32, 48));
                rect.move(0,5);
            case Face::Left:
                rect.setSize(sf::Vector2f(48, 32));
                rect.move(-5,0);
                break;
            case Face::Right:
                rect.setSize(sf::Vector2f(48, 32));
                rect.move(-3,0);
                break;
        }
        if (rect.getGlobalBounds().intersects(enemies[i]->rect.getGlobalBounds())){
            *index=i;
            return true;
        }
    }
    return false;
}

WeaponType GameLevel::matchRole() {
    if(hero->getRole()==CharacterClass::Thief)
        return WeaponType::Dagger;
    else if (hero->getRole()==CharacterClass::Mage)
        return WeaponType::Staff;
    else
        return WeaponType::Sword;

}

