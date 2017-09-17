#include "manager.h"

Manager::Manager(int ID)
    :EmployeeWithSubordinates(ID)
{}

double Manager::GetSalary()
{
    double sum = Employee::GetSalary();
    sum += GetSalaryForSub();
    return sum;
}

double Manager::GetSalaryForLOS()
{
    return Employee::GetSalaryForLOS() - GetSalaryForSub();
}

double Manager::GetSalaryForSub()
{
    double sumSubordinates = 0;
    for(auto ptr : subordinates)
        sumSubordinates += ptr->GetSalary();
    double sum = sumSubordinates * GetCurrentPosition()->GetConcretPosition()->GetPremiumForSubordinate();
    return sum;
}

QString Manager::GetSubordinatesInfoString()
{
    QString result;
    for(auto ptr : subordinates)
        result += ptr->GetSmallName() + " " +
                ptr->GetCurrentPosition()->GetConcretPosition()->GetName() + "\n";
    return result;
}

int Manager::GetSubCount()
{
    return GetSubFLCount();
}

int Manager::GetSubFLCount()
{
    return subordinates.size();
}
