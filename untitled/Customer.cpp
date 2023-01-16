

#include "Customer.h"
#include "Scheduler.h"

Customer::Customer(int id) : id_(id) {
    systemArrivalTime_ = Scheduler :: now();
}
