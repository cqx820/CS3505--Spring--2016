#ifndef BUOYANCY_H
#define BUOYANCY_H
#include "buoyancylogic.h"
#include "mycontactlistener.h"

class Buoyancy
{
public:
    Buoyancy(MyContactListner *listner);
    ~Buoyancy();
    void Step();
private:
    MyContactListner *listener;
    BuoyancyLogic *logic;
};

#endif // BUOYANCY_H
