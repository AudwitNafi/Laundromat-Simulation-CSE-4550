

#ifndef UNTITLED_LAUNDRY_H
#define UNTITLED_LAUNDRY_H


#include "Customer.h"
#include "Server.h"
#include "ArrivalEvent.h"
#include "Washer.h"
#include "Dryer.h"

class Laundry {
private:
    vector <Washer*> washers;
    vector <Dryer*> dryers;

    ArrivalEvent a_;

    int customersArrived_;
    double arrivalMean_;


    Washer* getShortestQueueWasher();
    Dryer* getShortestQueueDryer();

public:
    Laundry (int numWashers, int numDryers);
    void initialize();

    inline double& arrivalMean() { return arrivalMean_; }


    void arrivalHandler ();
    void departureHandler (Customer* cus);

};


#endif //UNTITLED_LAUNDRY_H
