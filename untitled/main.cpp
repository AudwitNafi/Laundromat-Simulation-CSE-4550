#include <iostream>
#include "Laundry.h"
#include "Scheduler.h"

int main() {
    int washerNumber[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int dryerNumber[10] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    Scheduler* sch = new Scheduler();
    Laundry* laundry = new Laundry(washerNumber[0], dryerNumber[0]);

    for(int i=0; i<10; i++)
    {
        sch -> initialize();
        laundry -> initialize(washerNumber[i], dryerNumber[i]);
        sch->run();
        laundry->report();
        laundry->csvfile<<i+1<<','<<washerNumber[i]<<','<<dryerNumber[i]<<','<<laundry->avgWasherDelay<<','<<laundry->avgDryerDelay<<','<<laundry->customersArrived_<<','<<laundry->customersLeft_<<','<<laundry->totalUtil << '\n';
    }

    delete laundry;
    delete sch;
    return 0;
}
