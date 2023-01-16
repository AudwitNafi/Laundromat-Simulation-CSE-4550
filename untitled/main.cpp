#include <iostream>
#include "Laundry.h"
#include "Scheduler.h"

int main() {
    Scheduler* sch = new Scheduler();
    Laundry* laundry = new Laundry(2, 2);
    sch -> initialize();
    laundry -> initialize();
    sch->run();
    return 0;
}
