//
// Created by Francesco Amorosini on 30/09/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_SPELL_H
#define PROGETTO_PROGRAMMAZIONE_SPELL_H


#include "DrawableObject.h"
#include "GameCharacter.h"

class Spell : public DrawableObject {
public:

    Spell(float x, float y, Face face);

    void updateSpell();

    Face face;
    float spellSpeed = 3.5;
    int spellRange=0;
    int static maxSpellRange;

    sf::Clock static projectileLife;
    sf::Time static projectileLifeSpan;
};




#endif //PROGETTO_PROGRAMMAZIONE_SPELL_H
