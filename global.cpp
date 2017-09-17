#include "global.h"

QSqlQuery ExecSQLQuery(QString QueryStr)
{
    QSqlQuery query;
    if(!query.exec(QueryStr))
    {
        qDebug() << "Unable QUERY!  " + QueryStr;
    }
    return query;
}
