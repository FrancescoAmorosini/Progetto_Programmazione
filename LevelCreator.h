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
    static int loadLevelExample(GameLevel* level);
    static int characterSelection(sf::RenderWindow* window);
    static GameLevel* createExample();


    static CharacterClass heroclass;
    std::string heroname;

};


#endif //PROGETTO_PROGRAMMAZIONE_GAMELEVELFACTORY_H
