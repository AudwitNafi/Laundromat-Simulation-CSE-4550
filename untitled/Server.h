//
// Created by Administrator on 1/10/2023.
//

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H


#include "Customer.h"
#include "DepartureEvent.h"
//#include "Laundry.h"
#include <queue>
#include "Scheduler.h"
using namespace std;

class Laundry;

class Server {
protected:

    Laundry* laundry;
    queue <Customer*> queue_;
    int status_;

    Customer* customerInService_;

    //Statistical variables
    double timeLastEvent_;
    double areaBusy_;
    double areaQueue_;
    double totalQueueingDelay_;
    double delay_;
    double totalServerDelay_;
    double serverDelay_;
    int customersArrived_;
    int customersServed_;
    int customersLeft_;
    int maxQueueLength_;
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
    inline double& getTotalServerDelay() { return totalServerDelay_; }
    inline double getAvgServerUtil(){return 100 * areaBusy_ / Scheduler :: now();}
    inline int getID(){ return id_;}
    inline int getCusServed(){ return customersServed_;}
    inline int getCusLeft(){ return customersLeft_;}
    virtual void arrivalHandler(Customer* cus) = 0;
    virtual void departureHandler() = 0;

    void updateStat ();

    static double exponential (double mean);
    bool chooseDryer ();
    void report();
};


#endif //UNTITLED_SERVER_H
