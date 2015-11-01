#include "transaction.h"

Transaction::Transaction()
{
    m_Amount = 0;
    m_NAV = 0;
    m_Units = 0;

}

Transaction::Transaction(const QDate &date,double amount, double nav, double units)
{
    m_Date = date;
    m_Amount = amount;
    m_NAV = nav;
    m_Units = units;
}

Transaction::~Transaction() {
    // TODO Auto-generated destructor stub
}


