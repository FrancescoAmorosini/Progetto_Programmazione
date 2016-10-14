//
// Created by Francesco Amorosini on 26/08/16.
//

#include "RNG.h"

bool RNG::initialized = false;

int RNG::throwDice(int faces) {
    if (!initialized) {
        std::srand( time(0) );
        initialized = true;
    }
    return std::rand() % faces + 1;

}

bool RNG::throwCoin(int probability) {
    if (!initialized) {
        std::srand( time(0) );
        initialized = true;
    }

    int randomNumber= std::rand();
    float random= (randomNumber % probability);

    if(!random)
        return true;
    else
        return false;
}