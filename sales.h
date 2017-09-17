#ifndef SALES_H
#define SALES_H

#include "employeewithsubordinates.h"

class Sales : public EmployeeWithSubordinates
{
public:
    Sales(int);
    virtual double GetSalary();
    // Length Of Service (LOS)
    virtual double GetSalaryForLOS();
    // Subordinates(Sub)
    virtual double GetSalaryForSub();
    virtual QString GetSubordinatesInfoString();
    // Count of subordinates
    virtual int GetSubCount();
    // Count of subordinates First Level
    virtual int GetSubFLCount();
protected:
    double RecurseSalary(std::shared_ptr<Employee> curr);
    QString RecurseSubordinatesInfo(QString prefix, std::shared_ptr<Employee> curr);
    int RecurseSubCount(std::shared_ptr<Employee> curr);
};

#endif // SALES_H
