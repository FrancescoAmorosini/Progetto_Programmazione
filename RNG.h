//
// Created by Francesco Amorosini on 26/08/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_DICE_H
#define PROGETTO_PROGRAMMAZIONE_DICE_H

#include <cstdlib>
#include <ctime>

class RNG {
public:
    static int throwDice(int faces);
    static bool throwCoin(int probability);
    static bool initialized;
};


#endif //PROGETTO_PROGRAMMAZIONE_DICE_H
