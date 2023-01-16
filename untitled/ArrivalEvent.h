

#ifndef UNTITLED_ARRIVALEVENT_H
#define UNTITLED_ARRIVALEVENT_H


#include "Event.h"

class Laundry;

class ArrivalEvent : public Event {
private:
    Laundry* laundry;
public:
    ArrivalEvent (Laundry* l) : laundry(l) { }
    void handle ();
};


#endif //UNTITLED_ARRIVALEVENT_H
