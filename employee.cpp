#include "employee.h"

Employee::Employee(int ID)
    :Person(ID)
{
    QString strQuery = "SELECT name FROM position INNER JOIN "
                       "(SELECT idPosition,dateEnd FROM person_position where idPerson=%1) AS tmp "
                       "ON ID=tmp.idPosition AND tmp.dateEnd IS NULL";
    strQuery = strQuery.arg(ID);
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "ERROR!";

    if(query.value(0).toString()=="Employee")
        type = PersonType::Employee;
    else if(query.value(0).toString()=="Manager")
        type = PersonType::Manager;
    else if(query.value(0).toString()=="Sales")
        type = PersonType::Sales;
    else if(query.value(0).toString()=="CEO")
        type = PersonType::CEO;

}

std::vector<std::shared_ptr<PersonInPosition> > Employee::GetPositions()
{
    return positions;
}

std::shared_ptr<PersonInPosition> Employee::GetCurrentPosition()
{
    for(auto ptr : positions)
        if(ptr->GetEndDate().isNull())
            return ptr;
    return nullptr;
}

QString Employee::GetPositionsInfoString()
{
    QString result;
    for(auto ptr : positions)
    {
        result += "C " + ptr->GetBeginDate().toString("yyyy-M-d") + " по ";
        if(ptr->GetEndDate().isNull())
            result += "Настоящее время";
        else
            result += ptr->GetEndDate().toString("yyyy-M-d");
        result += " " + ptr->GetConcretPosition()->GetName() + "\n";
        result += "_____________________________________\n";
    }
    return result;
}

PersonType Employee::GetType()
{
    return type;
}

double Employee::GetSalaryForLOS()
{
    return GetSalary() - GetCurrentPosition()->GetConcretPosition()->GetRate();
}

void Employee::AddPosition(std::shared_ptr<PersonInPosition> arg)
{
    positions.push_back(arg);
}

double Employee::GetSalary()
{
    if(!GetIsWorks())
        return 0;
    double sum = 0;
    double rate;
    double lengthOfService;
    double maxLOS;
    QDate dateBegin;
    QDate dateEND;

    QString strQuery = "SELECT * FROM position INNER JOIN person_position ON idPerson=%1 AND idPosition=position.ID;";
    strQuery = strQuery.arg(ID);

    QSqlQuery query = ExecSQLQuery(strQuery);
    QSqlRecord rec = query.record();
    while(query.next())
    {
        rate = query.value(rec.indexOf("rate")).toDouble();
        lengthOfService = query.value(rec.indexOf("lengthOfService")).toDouble();
        maxLOS = query.value(rec.indexOf("maxLOS")).toDouble();
        dateBegin = QDateTime::fromString(query.value(rec.indexOf("dateBegin")).toString(),
                                          "yyyy-M-d h:m:s:z").date();



        dateEND = QDateTime::fromString(query.value(rec.indexOf("dateEND")).toString(),
                                        "yyyy-M-d h:m:s:z").date();

        double koef;
        if(dateEND.isNull())
            koef = qPow(lengthOfService,(dateBegin.daysTo(QDate::currentDate())/365));
        else
            koef = qPow(lengthOfService,(dateBegin.daysTo(dateEND)/365))-1;
        if(koef>maxLOS)
            koef=maxLOS;
        sum += rate*(koef);
    }
    return sum;
}
