#include "position.h"

Position::Position(int ID)
{
    this->ID=ID;
}

QString Position::GetName()
{
    QString strQuery = "SELECT name FROM position where ID=%1";
    strQuery = strQuery.arg(ID);
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND NAME!";

    return query.value(0).toString();
}

int Position::GetID()
{
    return ID;
}

int Position::GetCount()
{
    QString strQuery = "SELECT COUNT(*) FROM person_position WHERE idPosition=%1";
    strQuery = strQuery.arg(ID);
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND NOONE!";
    return query.value(0).toInt();
}

double Position::GetRate()
{
    QString strQuery = "SELECT rate FROM position where ID=%1";
    strQuery = strQuery.arg(ID);
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND RATE!";

    return query.value(0).toDouble();
}

double Position::GetLengthOfServicePrecent()
{
    QString strQuery = "SELECT lengthOfService FROM position where ID=%1";
    strQuery = strQuery.arg(ID);
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND LOS!";

    return query.value(0).toDouble();
}

double Position::GetMaxLengthOfServicePrecent()
{
    QString strQuery = "SELECT maxLOS FROM position where ID=%1";
    strQuery = strQuery.arg(ID);
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND maxLOS!";

    return query.value(0).toDouble();
}

double Position::GetPremiumForSubordinate()
{
    QString strQuery = "SELECT premiumForSubordinate FROM position where ID=%1";
    strQuery = strQuery.arg(ID);
    QSqlQuery query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND PFS!";

    return query.value(0).toDouble();
}
