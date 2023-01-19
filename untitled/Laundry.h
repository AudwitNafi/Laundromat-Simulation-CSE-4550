

#ifndef UNTITLED_LAUNDRY_H
#define UNTITLED_LAUNDRY_H


#include <fstream>
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


    double arrivalMean_;


    Washer* getShortestQueueWasher();
    Dryer* getShortestQueueDryer();

public:
    int customersArrived_;
    std::ofstream csvfile;
    double totalWasherDelay;
    double totalDryerDelay;
    int totalWasherCus;
    int totalDryerCus;
    double avgWasherDelay;
    double avgDryerDelay;
    double totalUtil;
    int customersLeft_;
    Laundry (int numWashers, int numDryers);
    void initialize(int, int);
    ~Laundry();

    inline double& arrivalMean() { return arrivalMean_; }


    void arrivalHandler ();
    void departureHandler (Customer* cus);
    void report();
    void createCSV();
};


#endif //UNTITLED_LAUNDRY_H
