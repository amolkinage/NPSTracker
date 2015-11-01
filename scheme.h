#ifndef SCHEME_H
#define SCHEME_H

#include <QStringList>
#include "transaction.h"
#include "xirrtransaction.h"

class Scheme
{
public:
    Scheme();
    Scheme(const QString &name,int code, double nav,QDate navdate);

    virtual ~Scheme();
public:
    void   ReadFromDB();

    double getAmoutInvested() const {return m_AmtInvested;}
    double getMarketValue()   const {return m_CurrMarketValue;}
    double getGain()          const {return m_Gain;}
    double getCAGR()          const {return m_CAGR;}
    double getReturns()       const {return m_absReturn;}
    QString getName()         const { return m_name; }
    int     getCode()         const { return m_code; }

    xirrTransactions getxirrTransactions();

    void UpdateFromTransactions();

private:
    QString m_name;
    QDate m_NAVDate;
    int    m_code;
    double m_NAV;
    double m_AmtInvested;
    double m_CurrMarketValue;
    double m_TotalUnits;
    double m_AverageNAV;
    double m_Gain;
    double m_absReturn;
    double m_CAGR;

    QList<Transaction> m_Transactions;
};

#endif // SCHEME_H
