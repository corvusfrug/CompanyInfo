#include "sales.h"

Sales::Sales(int ID)
    :EmployeeWithSubordinates(ID)
{}

double Sales::GetSalary()
{
    double sum = Employee::GetSalary();
    sum += GetSalaryForSub();
    return sum;
}

double Sales::GetSalaryForLOS()
{
    return Employee::GetSalaryForLOS() - GetSalaryForSub();
}

double Sales::GetSalaryForSub()
{
    double sumSubordinates = 0;
    for(auto ptr: subordinates)
    {
        sumSubordinates += RecurseSalary(ptr);
    }
    double sum = sumSubordinates * GetCurrentPosition()->
            GetConcretPosition()->GetPremiumForSubordinate();
    return sum;
}

QString Sales::GetSubordinatesInfoString()
{
    QString result;
    for(auto ptr: subordinates)
    {
        result += ptr->GetSmallName() + "\n";
        result += RecurseSubordinatesInfo("----", ptr);
    }
    return result;
}

int Sales::GetSubCount()
{
    int sum = GetSubFLCount();
    for(auto ptr: subordinates)
    {
        sum += RecurseSubCount(ptr);
    }
    return sum;
}

int Sales::GetSubFLCount()
{
    return subordinates.size();
}

double Sales::RecurseSalary(std::shared_ptr<Employee> curr)
{
    double sum=curr->GetSalary();
    if(curr->GetType()==PersonType::Employee)
        return sum;
    auto tmp = std::dynamic_pointer_cast<EmployeeWithSubordinates>(curr);
    for(auto ptr: tmp->GetSubordinates())
    {
        sum += RecurseSalary(ptr);
    }
    return sum;
}

QString Sales::RecurseSubordinatesInfo(QString prefix, std::shared_ptr<Employee> curr)
{
    QString result;
    if(curr->GetType()==PersonType::Employee)
        return result;
    auto tmp = std::dynamic_pointer_cast<EmployeeWithSubordinates>(curr);
    for(auto ptr: tmp->GetSubordinates())
    {
        result += prefix + ">" + ptr->GetSmallName() + "\n";
        result += RecurseSubordinatesInfo(prefix+"----", ptr);
    }
    return result;
}

int Sales::RecurseSubCount(std::shared_ptr<Employee> curr)
{
    int sum = 0;
    if(curr->GetType()==PersonType::Employee)
        return sum;
    auto tmp = std::dynamic_pointer_cast<EmployeeWithSubordinates>(curr);
    sum = tmp->GetSubFLCount();
    for(auto ptr: tmp->GetSubordinates())
    {
        sum += RecurseSubCount(ptr);
    }
    return sum;
}
