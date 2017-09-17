#include "person.h"

Person::Person( int ID)
{
    this->ID=ID;
}

QString Person::GetSecondName()
{
    QSqlQuery query;
    QString strQuery = "SELECT sname FROM person where ID=%1";
    strQuery = strQuery.arg(ID);
    query = ExecSQLQuery(strQuery);

    if(!query.next())
    {
        qDebug() << "NOT FIND NAME!";
    }

    return query.value(0).toString();
}

QString Person::GetFirstName()
{
    QSqlQuery query;
    QString strQuery = "SELECT fname FROM person where ID=%1";
    strQuery = strQuery.arg(ID);
    query = ExecSQLQuery(strQuery);

    if(!query.next())
    {
        qDebug() << "NOT FIND FIRST NAME!";
    }

    return query.value(0).toString();
}

QString Person::GetFullName()
{
    return GetFirstName() + " " + GetSecondName() + " " + GetLastName();
}

QString Person::GetSmallName()
{
    return GetFirstName()[0] + ". " + GetSecondName()[0] + ". " + GetLastName();
}

int Person::GetID()
{
    return ID;
}

bool Person::GetIsWorks()
{
    QSqlQuery query;
    QString strQuery = "SELECT isworks FROM person where ID=%1";
    strQuery = strQuery.arg(ID);
    query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND isworks!";

    return query.value(0).toBool();

}

QString Person::GetLastName()
{
    //qDebug() << db.use_count();
    QSqlQuery query;
    QString strQuery = "SELECT lname FROM person where ID=%1";
    strQuery = strQuery.arg(ID);
    query = ExecSQLQuery(strQuery);

    if(!query.next())
    {
        qDebug() << "NOT FIND NAME!";
    }

    return query.value(0).toString();

}
