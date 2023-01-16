//
// Created by Administrator on 1/10/2023.
//

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H


#include "Customer.h"
#include "DepartureEvent.h"
//#include "Laundry.h"
#include <queue>
using namespace std;

class Laundry;

class Server {
protected:

    Laundry* laundry;
    queue <Customer*> queue_;
    int status_;

    Customer* customerInService_;

    double timeLastEvent_;
    double areaBusy_;
    double areaQueue_;
    double totalQueueingDelay_;
    double totalServerDelay_;

    int id_;
    double departureMean_;
    double dryerProbability_;

    DepartureEvent d_;

public:

    Server(int id, double departureMean, Laundry* l);
    void initialize();

    inline int& status() { return status_; }
    inline int queueLength() { return queue_.size(); }
    inline double& departureMean() { return departureMean_; }
    inline double& dryerProbability() { return dryerProbability_; }

    virtual void arrivalHandler(Customer* cus) = 0;
    virtual void departureHandler() = 0;

    void updateStat ();

    static double exponential (double mean);
    bool chooseDryer ();
};


#endif //UNTITLED_SERVER_H
