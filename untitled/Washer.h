

#ifndef UNTITLED_WASHER_H
#define UNTITLED_WASHER_H


#include "Server.h"

class Washer : public Server {
public:
    Washer (int id, double departureMean, Laundry* l);
    void arrivalHandler (Customer* cus) override;
    void departureHandler () override;
};


#endif //UNTITLED_WASHER_H
