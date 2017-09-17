#ifndef COMPANY_H
#define COMPANY_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "employee.h"
#include "personinposition.h"
#include "position.h"
#include "manager.h"
#include "sales.h"

class Company : public QObject
{
    Q_OBJECT
public:
    Company();
    double GetTotalMoney();
    int GetCountEmployee();
    std::shared_ptr<Employee> GetCEO();
    std::vector<std::shared_ptr<Position>>& GetPositions();
    std::vector<std::shared_ptr<Employee>>& GetPersons();
private:
    void init();
    std::shared_ptr<Position> findPositionByID(int ID);
    std::shared_ptr<Employee> findPersonByID(int ID);
    std::shared_ptr<Employee> CEO = nullptr;
    std::shared_ptr<QSqlDatabase> db = nullptr;
    std::vector<std::shared_ptr<Position>> positions;
    std::vector<std::shared_ptr<PersonInPosition>> person_position;
    std::vector<std::shared_ptr<Employee>> persons;
};

#endif // COMPANY_H
