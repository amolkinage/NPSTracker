#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDate>

class Transaction
{
public:
    Transaction();
    Transaction(const QDate &date,double amount, double nav, double units);
    virtual ~Transaction();

public:
    QDate  GetDate(){return m_Date;}
    double GetAmount(){return m_Amount;}
    double GetNAV(){return m_NAV;}
    double GetUnits(){return m_Units;}

private:
    QDate   m_Date;
    double  m_Amount;
    double  m_NAV;
    double  m_Units;
};

#endif // TRANSACTION_H
