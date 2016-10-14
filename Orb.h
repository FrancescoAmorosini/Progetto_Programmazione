//
// Created by Francesco Amorosini on 22/06/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ORB_H
#define PROGETTO_PROGRAMMAZIONE_ORB_H

#include "PlayableCharacter.h"

enum class Color {yellow,red,green,blue,purple};

class Orb : public DrawableObject {
public:
    Orb(float x, float y, Color c);

    void useOrb(PlayableCharacter* hero);

    Color getOrbColor() const;


private:
    Color orbColor;

};


#endif //PROGETTO_PROGRAMMAZIONE_ORB_H
