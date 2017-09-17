#ifndef MANAGER_H
#define MANAGER_H

#include "employeewithsubordinates.h"

class Manager : public EmployeeWithSubordinates
{
public:
    Manager(int);
    virtual double GetSalary();
    // Length Of Service (LOS)
    virtual double GetSalaryForLOS();
    // Subordinates (Sub)
    virtual double GetSalaryForSub();
    virtual QString GetSubordinatesInfoString();
    // Count of subordinates
    virtual int GetSubCount();
    // Count of subordinates First Level
    virtual int GetSubFLCount();
};

#endif // MANAGER_H
