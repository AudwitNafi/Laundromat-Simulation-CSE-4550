

#ifndef UNTITLED_DRYER_H
#define UNTITLED_DRYER_H


#include "Server.h"

class Dryer : public Server {
public:
    Dryer(int id, double departureMean, Laundry* l);
    void arrivalHandler (Customer* cus) override;
    void departureHandler () override;
};


#endif //UNTITLED_DRYER_H
