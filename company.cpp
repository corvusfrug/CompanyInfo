#include "company.h"

Company::Company()
{
    db = std::shared_ptr<QSqlDatabase>(new QSqlDatabase);
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("db\\MyCompany.db");
    if (!db->open())
    {
        qDebug() << "Cannot open database:"
               << db->lastError();
    }
    init();
}

double Company::GetTotalMoney()
{
    double sum = 0;
    for(auto ptr : persons)
        sum += ptr->GetSalary();

    return sum;
}

void Company::init()
{
    //positions;
    QString strQuery = "SELECT ID FROM position";
    QSqlQuery query = ExecSQLQuery(strQuery);
    while(query.next())
    {
        positions.push_back(  std::shared_ptr<Position>( new Position(query.value(0).toInt()) )  );
    };

    //persons;
    strQuery = "SELECT person.ID, position.name FROM person INNER JOIN person_position INNER JOIN position ON person.ID=idPerson AND idPosition=position.ID AND person.isworks=1 AND person_position.dateEnd IS NULL";
    query = ExecSQLQuery(strQuery);
    while(query.next())
    {
        QString str = query.value(1).toString();
        if(str=="Employee")
            persons.push_back( std::shared_ptr<Employee>( new Employee(query.value(0).toInt())));
        else if(str=="Sales")
            persons.push_back( std::shared_ptr<Employee>( new Sales(query.value(0).toInt())));
        else if(str=="Manager")
            persons.push_back( std::shared_ptr<Employee>( new Manager(query.value(0).toInt())));
        else if(str=="CEO")
        {
            persons.push_back( std::shared_ptr<Employee>( new Manager(query.value(0).toInt())));
            CEO = persons.back();
        }
    }

    //person - position
    std::shared_ptr<Employee> tmpEmpl;
    std::shared_ptr<Position> tmpPos;
    strQuery = "SELECT idPerson, idPosition FROM person_position";
    query = ExecSQLQuery(strQuery);
    while(query.next())
    {
        tmpEmpl = findPersonByID(query.value(0).toInt());
        tmpPos = findPositionByID(query.value(1).toInt());
        person_position.push_back(
                    std::shared_ptr<PersonInPosition>( new PersonInPosition( tmpEmpl, tmpPos ))
                    );
        tmpEmpl->AddPosition(person_position.back());
    }

    strQuery = "SELECT idHead, idSubordinate FROM head_subordinate";
    query = ExecSQLQuery(strQuery);
    while(query.next())
    {
        if(query.value(0).toInt()==query.value(1).toInt()) continue;
        std::shared_ptr<EmployeeWithSubordinates> tmpptrHead =
          std::dynamic_pointer_cast<EmployeeWithSubordinates>(findPersonByID(query.value(0).toInt()));
        tmpptrHead->AddSubordinates(findPersonByID(query.value(1).toInt()));
    }
}


int Company::GetCountEmployee()
{
    QSqlQuery query;
    QString strQuery = "SELECT COUNT(*) FROM person WHERE isworks=1";
    query = ExecSQLQuery(strQuery);
    if(!query.next())
        qDebug() << "NOT FIND CEO!";
    return query.value(0).toInt();
}

std::shared_ptr<Employee> Company::GetCEO()
{
    return CEO;
}

std::vector<std::shared_ptr<Position>>& Company::GetPositions()
{
    return positions;
}

std::vector<std::shared_ptr<Employee> >& Company::GetPersons()
{
    return persons;
}

std::shared_ptr<Position> Company::findPositionByID(int ID)
{
    for(auto ptr : positions)
        if(ptr->GetID()==ID)
            return ptr;
    return nullptr;
}

std::shared_ptr<Employee> Company::findPersonByID(int ID)
{
    for(auto ptr : persons)
        if(ptr->GetID()==ID)
            return ptr;
    return nullptr;
}
