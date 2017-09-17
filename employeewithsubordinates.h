#ifndef EMPLOYEEWITHSUBORDINATES_H
#define EMPLOYEEWITHSUBORDINATES_H

#include "employee.h"


class EmployeeWithSubordinates : public Employee
{
public:
    std::vector<std::shared_ptr<Employee> > GetSubordinates();
    virtual double GetSalary() = 0;
    virtual QString GetSubordinatesInfoString() = 0;
    // Length Of Service (LOS)
    virtual double GetSalaryForLOS() = 0;
    // Subordinates(Sub)
    virtual double GetSalaryForSub() = 0;
    // Count of subordinates
    virtual int GetSubCount() = 0;
    // Subordinates(Sub) First Level(FL)
    virtual int GetSubFLCount() = 0;
    //bool SetSubordinates(std::vector<std::shared_ptr<Employee> > subordinates);
    void AddSubordinates(std::shared_ptr<Employee>);
protected:
    EmployeeWithSubordinates(int);
    std::vector<std::shared_ptr<Employee> > subordinates;
};

#endif // EMPLOYEEWITHSUBORDINATES_H
