

#include "Laundry.h"
#include "Washer.h"
#include "Scheduler.h"

Washer::Washer(int id, double departureMean, Laundry* l) : Server(id, departureMean, l) {
}

void Washer::arrivalHandler(Customer *cus) {
    updateStat();
    customersArrived_++;
    if (status() == 0) {
        status() = 1;
        customerInService_ = cus;
        delay_ = Scheduler::now() - cus -> serverArrivalTime();
        totalQueueingDelay_ += delay_;

        double t = Server :: exponential(departureMean_);
        d_.activate(t);
    } else {
        queue_.push(cus);
    }
}

void Washer::departureHandler() {
    updateStat();
    status() = 0;
    customersServed_++;

    serverDelay_ = Scheduler::now() - customerInService_->serverArrivalTime();
    totalServerDelay_ += serverDelay_;


    if (chooseDryer()) {
        laundry->departureHandler(customerInService_);
    } // else leave system

    if (queueLength() > 0) {
        status() = 1;
        customerInService_ = queue_.front();
        queue_.pop();

        delay_ = Scheduler::now() - customerInService_ -> serverArrivalTime();
        totalQueueingDelay_ += delay_;

        double t = Server :: exponential(departureMean_);
        d_.activate(t);
    } else {
        customerInService_ = nullptr;
    }
}
