//
// Created by francesco amorosini on 04/11/16.
//

#ifndef PROGETTO_PROGRAMMAZIONE_OBSERVER_H
#define PROGETTO_PROGRAMMAZIONE_OBSERVER_H
class Observer{
public:
    virtual void update()=0;

    virtual void attach () =0;

    virtual void detach() =0;
};
#endif //PROGETTO_PROGRAMMAZIONE_OBSERVER_H
