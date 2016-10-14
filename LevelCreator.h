//
// Created by Francesco Amorosini on 26/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_GAMELEVELFACTORY_H
#define PROGETTO_PROGRAMMAZIONE_GAMELEVELFACTORY_H

#include "LevelCreator.h"
#include "GameLevel.h"

class LevelCreator {
public:
    //la costruzione di ogni livello dovrà essere un metodo, al termine di ogni metodo costruttore verrà lanciato il metodo loadLevel
    static GameLevel* loadLevel(Map* map, PlayableCharacter* hero, std::vector<Chest*> chests,
                                  std::vector<Weapon*> weapons, std::vector<Orb*> orbs, std::vector<Enemy*> enemies, std::vector<Heart*> hearts);
    static GameLevel* createExample();

};


#endif //PROGETTO_PROGRAMMAZIONE_GAMELEVELFACTORY_H
