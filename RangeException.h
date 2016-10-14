//
// Created by Francesco Amorosini on 08/07/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_RANGEEXCEPTION_H
#define PROGETTO_PROGRAMMAZIONE_RANGEEXCEPTION_H

#endif //PROGETTO_PROGRAMMAZIONE_RANGEEXCEPTION_H
#include <stdexcept>  // Standard Library exceptions
#include <string>

class RangeException : public std::out_of_range {
public:
    RangeException(std::string error, int min, int max, int errValue) : std::out_of_range(error), minRange(min),
                                                                             maxRange(max), wrongRange(errValue){}

    int getMinRange() const {
        return minRange;
    }
    int getMaxRange() const {
        return maxRange;
    }
    int getWrongRange() const {
        return wrongRange;
    }

private:
    int minRange;
    int maxRange;
    int wrongRange;

};
