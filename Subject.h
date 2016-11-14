//
// Created by francesco amorosini on 04/11/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_SUBJECT_H
#define PROGETTO_PROGRAMMAZIONE_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual void registerObserver(Observer *o)=0;
    virtual void unregisterObserver(Observer *o)=0;
    virtual void notify() const =0;

    virtual ~Subject() {}

};
#endif //PROGETTO_PROGRAMMAZIONE_SUBJECT_H
