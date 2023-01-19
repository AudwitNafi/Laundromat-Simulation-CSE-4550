

#include "DepartureEvent.h"
#include "Server.h"

DepartureEvent::DepartureEvent(Server *s) : server(s) {

}

void DepartureEvent::handle() {
    server -> departureHandler();
}