

#ifndef UNTITLED_CUSTOMER_H
#define UNTITLED_CUSTOMER_H


class Customer {
private:
    int id_;
    double systemArrivalTime_;
    double serverArrivalTime_;

public:
    Customer (int id);

    inline double id() { return id_; }
    inline double systemArrivalTime() { return systemArrivalTime_; }
    inline double serverArrivalTime() { return serverArrivalTime_; }

};


#endif //UNTITLED_CUSTOMER_H
