#ifndef PERSON_H
#define PERSON_H

#include "global.h"

class Person
{
public:
    Person(int);
    QString GetLastName();
    QString GetSecondName();
    QString GetFirstName();
    QString GetFullName();
    // И. И. Иванов
    QString GetSmallName();
    int GetID();
    // Работает ли сейчас?
    bool GetIsWorks();
protected:
    int ID;
};

#endif // PERSON_H
