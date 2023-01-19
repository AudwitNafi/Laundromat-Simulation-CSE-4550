

#include "ArrivalEvent.h"
#include "Laundry.h"

// handle an arrival event
void
ArrivalEvent :: handle () {
    laundry -> arrivalHandler();
}