

#include "Dryer.h"
#include "Scheduler.h"

void Dryer::arrivalHandler(Customer *cus) {
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

void Dryer::departureHandler() {
    updateStat();
    status() = 0;
    customersServed_++;
    {
        delay_ = Scheduler::now() - customerInService_->serverArrivalTime();
        totalServerDelay_ += delay_;
    }

    // leave system after service

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

Dryer::Dryer(int id, double departureMean, Laundry* l) : Server(id, departureMean, l) {

}
