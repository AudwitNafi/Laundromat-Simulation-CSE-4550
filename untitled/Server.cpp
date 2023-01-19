//
// Created by Administrator on 1/10/2023.
//
#include <iostream>
#include "Server.h"
#include <cmath>
#include "Scheduler.h"
using namespace std;

Server::Server(int id, double departureMean, Laundry* l) : id_(id), departureMean_(departureMean), d_(this), laundry(l){

}

void Server::initialize() {
    queue_ = queue <Customer*> ();
    status_ = 0;
    customersArrived_ = 0;
    customersServed_ = 0;
    customersLeft_ = 0;
    customerInService_ = nullptr;

    timeLastEvent_ = 0.0;
    areaBusy_ = 0.0;
    areaQueue_ = 0.0;
    totalQueueingDelay_ = 0.0;
    totalServerDelay_ = 0.0;
    maxQueueLength_ = 0;
    dryerProbability_ = 0.5;
}

double Server::exponential(double mean) {
    double r = (double)rand()/(RAND_MAX);
    double ex = -mean * log (r);
    return ex;
}

bool Server::chooseDryer() {
    double r = (double)rand()/(RAND_MAX);
    return (r < dryerProbability_);
}

void Server::updateStat() {
    double duration_ = Scheduler :: now() - timeLastEvent_;
    areaBusy_ += duration_ * status();
    areaQueue_ += duration_ * queueLength();
    timeLastEvent_ = Scheduler :: now();
    maxQueueLength_ = max(maxQueueLength_, queueLength());
}

void Server::report()
{
    updateStat();

    cout << "Total Customers Arrived: " << customersArrived_ << endl;

    cout << "Total Customers Served: " << customersServed_ <<endl;

    cout << "Total Customers Left Un-served: " << customersLeft_ <<endl;

    cout << "Average Server Utilization: " << 100 * areaBusy_ / Scheduler :: now() << "%" << endl;

    cout << "Average Queue Length: " << areaQueue_ / Scheduler :: now() << endl;

    cout << "Average Queue Delay: " << totalQueueingDelay_ / customersArrived_ << endl;

    cout << "Average Service Delay: " << totalServerDelay_ / customersServed_ << endl<<endl;

    // debug
    if (customersArrived_ != customersServed_ + customersLeft_) cout << "XXXXXXXXXX" <<endl;
}