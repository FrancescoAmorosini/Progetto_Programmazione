//
// Created by Francesco Amorosini on 22/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMELEVEL_H
#define PROGETTO_PROGRAMMAZIONE_GAMELEVEL_H

#include "PlayableCharacter.h"
#include "Enemy.h"
#include "Map.h"
#include "Wall.h"
#include "WeaponFactory.h"
#include "Chest.h"
#include "Spell.h"
#include "Heart.h"


class GameLevel {
public:
    GameLevel(Map* map, PlayableCharacter* hero, std::vector<Chest*> chests,
              std::vector<Orb*> orbs, std::vector<Enemy*> enemies, std::vector<Heart*> hearts);
    ~GameLevel(){
        chests.clear();
        weapons.clear();
        orbs.clear();
        enemies.clear();
        spells.clear();
        hearts.clear();
    }

    void updateLevel();

    void checkProjectileCollisions(Spell* spell, int* index);
    void checkOrbsCollisions();
    void checkHeartsCollisions();
    void checkEnemiesCollisions();
    void checkWeaponsCollisions();
    bool checkChestCollision(sf::RectangleShape rect, Face face, int *index);
    bool checkWallCollision(sf::RectangleShape rect, Face face, int* index);
    bool checkCloseEnemy(sf::RectangleShape rect, Face face, int* index);
    WeaponType matchRole();

    Map* map;
    PlayableCharacter* hero;
    std::vector<Chest*> chests;
    std::vector<Weapon*> weapons;
    std::vector<Orb*> orbs;
    std::vector<Enemy*> enemies;
    std::vector<Spell*> spells;
    std::vector<Heart*> hearts;



};


#endif //PROGETTO_PROGRAMMAZIONE_GAMELEVEL_H
