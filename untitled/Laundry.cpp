
#include <iostream>
#include "Laundry.h"
using namespace std;

Laundry::Laundry(int numWashers, int numDryers) : a_(this)
{
    createCSV();
}

Laundry::~Laundry()
{
    csvfile.close();
}

void Laundry::initialize(int numWashers, int numDryers) {
    washers = vector <Washer*> (numWashers);
    for (int i=0; i<numWashers; i++) {
        washers[i] = new Washer(i, 4.0, this);
        washers[i]->initialize();
    }
    dryers = vector <Dryer*> (numDryers);
    for (int i=0; i<numDryers; i++) {
        dryers[i] = new Dryer(i, 3.0, this);
        dryers[i]->initialize();
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

void Laundry::report() {
    totalWasherDelay = 0.0;
    totalDryerDelay = 0.0;
    totalWasherCus = 0;
    totalDryerCus = 0;
    avgWasherDelay = 0.0;
    avgDryerDelay = 0.0;
    totalUtil = 0.0;
    customersLeft_ = 0;
    for (auto w : washers) {
        cout << "For washer "<<w->getID()+1<<":"<<endl;
        cout<<"---------------------------------------"<<endl;
        w->report();
        totalWasherDelay += w->getTotalServerDelay();
        totalWasherCus += w->getCusServed();
        totalUtil += w->getAvgServerUtil();
        customersLeft_ += w->getCusLeft();
    }
    avgWasherDelay = totalWasherDelay/totalWasherCus;
    cout<<"Total Washer Delay: "<<totalWasherDelay<<"\n";
    cout<<"Average Washer Delay: "<<avgWasherDelay<<"\n\n";
    for(auto d : dryers){
        cout << "For dryer "<<d->getID()+1<<":"<<endl;
        cout<<"---------------------------------------"<<endl;
        d->report();
        totalDryerDelay += d->getTotalServerDelay();
        totalDryerCus += d->getCusServed();
        totalUtil += d->getAvgServerUtil();
        customersLeft_ += d->getCusLeft();
    }
    totalUtil /= 3;
    avgDryerDelay = totalDryerDelay/totalDryerCus;
    cout<<"Total Dryer Delay: "<<totalDryerDelay<<"\n";
    cout<<"Average Dryer Delay: "<<avgDryerDelay<<"\n\n";
    cout<<"Avg System Delay: " << avgWasherDelay + avgDryerDelay<<"\n";
    cout<<"Customers Left Unattended: "<<customersLeft_<<"\n";
    cout<<"Average System Utilization: "<<totalUtil<<"\n\n";
}

void Laundry::createCSV()
{
    csvfile.open("record.csv", ios::out);
    csvfile <<"Simulation Run" << "," << "#Washers" << ',' << "#Dryers" << ',' << "Avg Washing Time" << ',' << "Avg Drying Time" << ',' << "#Customers Arrived" << ',' << "#Customers Unattended" << ',' << "System Utilization(%)" << '\n';
}