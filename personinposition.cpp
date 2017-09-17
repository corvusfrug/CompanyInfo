#include "personinposition.h"

PersonInPosition::PersonInPosition(std::shared_ptr<Employee> person, std::shared_ptr<Position> position)
{
    this->person=person;
    this->position=position;
}

QDate PersonInPosition::GetBeginDate()
{
    QString strQuery = "SELECT dateBegin FROM person_position where idPerson=%1 AND idPosition=%2";
    strQuery = strQuery.arg(person->GetID()).arg(position->GetID());
    QSqlQuery query = ExecSQLQuery(strQuery);

    if(!query.next())
        qDebug() << "NOT FIND PFS!";

    return QDateTime::fromString(query.value(0).toString(),
                                      "yyyy-M-d h:m:s:z").date();
}

QDate PersonInPosition::GetEndDate()
{
    QString strQuery = "SELECT dateEnd FROM person_position where idPerson=%1 AND idPosition=%2";
    strQuery = strQuery.arg(person->GetID()).arg(position->GetID());
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND PFS!";

    return QDateTime::fromString(query.value(0).toString(),
                                 "yyyy-M-d h:m:s:z").date();
}

std::shared_ptr<Employee> PersonInPosition::GetConcretPerson()
{
    return person;
}

std::shared_ptr<Position> PersonInPosition::GetConcretPosition()
{
    return position;
}
