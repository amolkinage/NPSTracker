#ifndef XIRRTRANSACTION
#define XIRRTRANSACTION

#include <QDate>

struct xirrTransaction
{
    QDate  date;
    double amount;
};

typedef QList<xirrTransaction> xirrTransactions;

double CalculateXIRR(xirrTransactions transactions,double rate);

#endif // XIRRTRANSACTION

