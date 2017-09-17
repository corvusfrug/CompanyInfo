#ifndef POSITION_H
#define POSITION_H

#include "global.h"

class Position
{
public:
    Position(int);
    QString GetName();
    int GetID();
    int GetCount();
    // Ставка
    double GetRate();
    // хранится как коэффициент, при 3% хранится 1.03
    double GetLengthOfServicePrecent();
    double GetMaxLengthOfServicePrecent();
    double GetPremiumForSubordinate();
protected:
    int ID;
};

#endif // POSITION_H
