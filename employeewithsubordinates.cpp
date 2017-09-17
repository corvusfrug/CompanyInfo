#include "employeewithsubordinates.h"

EmployeeWithSubordinates::EmployeeWithSubordinates(int ID)
    :Employee(ID)
{}

std::vector<std::shared_ptr<Employee> > EmployeeWithSubordinates::GetSubordinates()
{
    return subordinates;
}

void EmployeeWithSubordinates::AddSubordinates(std::shared_ptr<Employee> arg)
{
    subordinates.push_back(arg);
}
/*
bool EmployeeWithSubordinates::SetSubordinates(std::vector<std::shared_ptr<Employee> > subordinates)
{
    // Проверка на правильность /
    for(auto ptr : subordinates)
    {
        QString strQuery = "SELECT idHead FROM head_subordinate WHERE idSubordinate=%1";
        strQuery = strQuery.arg(ptr->GetID());
        QSqlQuery query = ExecSQLQuery(strQuery);

        if(!query.next())
            return false;
        if(query.value(0).toInt()!=ID)
            return false;
    }
    // Проверка на правильность /

    this->subordinates=subordinates;
    return true;
}*/
