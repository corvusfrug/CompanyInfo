#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "personinposition.h"
#include "person.h"
#include "enumpersontype.h"
#include <memory>

class PersonInPosition;

class Employee : public Person
{
public:
    Employee(int);
    // Текущая должность
    std::shared_ptr<PersonInPosition> GetCurrentPosition();
    // Все должности
    std::vector<std::shared_ptr<PersonInPosition>> GetPositions();
    QString GetPositionsInfoString();
    PersonType GetType();
    void AddPosition(std::shared_ptr<PersonInPosition>);
    // Length Of Service (LOS)
    virtual double GetSalaryForLOS();
    virtual double GetSalary();
protected:
    std::vector<std::shared_ptr<PersonInPosition>> positions;
    PersonType type;
};

#endif // EMPLOYEE_H
