#ifndef PERSONINPOSITION_H
#define PERSONINPOSITION_H


#include "employee.h"
#include "position.h"
#include <memory>

class Employee;

class PersonInPosition
{
public:
    PersonInPosition(
            std::shared_ptr<Employee>,
            std::shared_ptr<Position>);
    QDate GetBeginDate();
    QDate GetEndDate();
    std::shared_ptr<Employee> GetConcretPerson();
    std::shared_ptr<Position> GetConcretPosition();
private:
    std::shared_ptr<Employee> person = nullptr;
    std::shared_ptr<Position> position = nullptr;


};

#endif // PERSONINPOSITION_H
