

#include "Laundry.h"

Laundry::Laundry(int numWashers, int numDryers) : a_(this){
    washers = vector <Washer*> (numWashers);
    for (int i=0; i<numWashers; i++) {
        washers[i] = new Washer(i, 4.0, this);
    }
    dryers = vector <Dryer*> (numDryers);
    for (int i=0; i<numDryers; i++) {
        dryers[i] = new Dryer(i, 3.0, this);
    }
}

void Laundry::initialize() {
    for(auto s : washers) {
        s -> initialize();
    }
    for(auto s : dryers) {
        s -> initialize();
    }

    customersArrived_ = 0;
    arrivalMean_ = 3.0;

    double t = Server :: exponential(arrivalMean_);
    a_.activate(t);

}

void Laundry::arrivalHandler() {
    Customer* cus = new Customer(customersArrived_ ++);

    // admit to shortest queue washer
    Washer* next = getShortestQueueWasher();
    next -> arrivalHandler(cus);

    if (customersArrived_ < 100) {
        double t = Server :: exponential(arrivalMean_);
        a_.activate(t);
    }
}

void Laundry::departureHandler(Customer *cus) {
    // admit to shortest queue dryer
    Dryer* next = getShortestQueueDryer();
    next -> arrivalHandler(cus);
}

Washer *Laundry::getShortestQueueWasher() {
    int sid = 0;
    for (int i = 0; i < washers.size(); ++i) {
        if (washers[i] -> status() + washers[i] -> queueLength()
            < washers[sid] -> status() + washers[sid] -> queueLength()) {
            sid = i;
        }
    }
    return washers[sid];
}

Dryer *Laundry::getShortestQueueDryer() {
    int sid = 0;
    for (int i = 0; i < dryers.size(); ++i) {
        if (dryers[i] -> status() + dryers[i] -> queueLength()
            < dryers[sid] -> status() + dryers[sid] -> queueLength()) {
            sid = i;
        }
    }
    return dryers[sid];
}
