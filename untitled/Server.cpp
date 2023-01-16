//
// Created by Administrator on 1/10/2023.
//

#include "Server.h"
#include <cmath>

Server::Server(int id, double departureMean, Laundry* l) : id_(id), departureMean_(departureMean), d_(this), laundry(l){

}

void Server::initialize() {
    queue_ = queue <Customer*> ();
    status_ = 0;

    customerInService_ = nullptr;

    timeLastEvent_ = 0.0;
    areaBusy_ = 0.0;
    areaQueue_ = 0.0;
    totalQueueingDelay_ = 0.0;
    totalServerDelay_ = 0.0;

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