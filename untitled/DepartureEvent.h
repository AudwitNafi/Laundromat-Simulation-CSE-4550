

#ifndef UNTITLED_DEPARTUREEVENT_H
#define UNTITLED_DEPARTUREEVENT_H


#include "Event.h"

class Server;

class DepartureEvent : public Event {
private:
    Server* server;
public:
    DepartureEvent (Server* s);
    void handle ();
};


#endif //UNTITLED_DEPARTUREEVENT_H
