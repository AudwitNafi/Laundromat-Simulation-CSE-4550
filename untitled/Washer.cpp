

#include "Laundry.h"
#include "Washer.h"
#include "Scheduler.h"

Washer::Washer(int id, double departureMean, Laundry* l) : Server(id, departureMean, l) {
}

void Washer::arrivalHandler(Customer *cus) {
    if (status() == 0) {
        status() = 1;
        customerInService_ = cus;
        double delay = Scheduler::now() - cus -> serverArrivalTime();
        totalQueueingDelay_ += delay;

        double t = Server :: exponential(departureMean_);
        d_.activate(t);
    } else {
        queue_.push(cus);
    }
}

void Washer::departureHandler() {
    status() = 0;
    {
        double delay = Scheduler::now() - customerInService_->serverArrivalTime();
        totalServerDelay_ += delay;
    }

    if (chooseDryer()) {
        laundry->departureHandler(customerInService_);
    } // else leave system

    if (queueLength() > 0) {
        status() = 1;
        customerInService_ = queue_.front();
        queue_.pop();

        double delay = Scheduler::now() - customerInService_ -> serverArrivalTime();
        totalQueueingDelay_ += delay;

        double t = Server :: exponential(departureMean_);
        d_.activate(t);
    } else {
        customerInService_ = nullptr;
    }
}
