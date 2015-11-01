#include "scheme.h"
#include <QtSql>

Scheme::Scheme()
{
    m_code = 0;
    m_NAV = 0;

    m_AmtInvested = 0;
    m_CurrMarketValue=0;
    m_TotalUnits=0;
    m_AverageNAV=0;
    m_Gain=0;
    m_CAGR=0;
}

Scheme::Scheme(const QString &name,int code, double nav,QDate navdate)
{
    m_name = name;
    m_code = code;
    m_NAV = nav;
    m_NAVDate = navdate;
    m_AmtInvested = 0;
    m_CurrMarketValue=0;
    m_TotalUnits=0;
    m_AverageNAV=0;
    m_Gain=0;
    m_CAGR=0;
}


Scheme::~Scheme() {
    // TODO Auto-generated destructor stub
}


xirrTransactions Scheme::getxirrTransactions()
{
    xirrTransactions xirrTransactionsList;

    for(int ii=0; ii < m_Transactions.count(); ii++)
    {
        if(m_Transactions[ii].GetAmount()!=0)
        {
            xirrTransaction xtran;
            xtran.amount = m_Transactions[ii].GetAmount();
            xtran.date = m_Transactions[ii].GetDate();
            xirrTransactionsList << xtran;
        }
    }
    return xirrTransactionsList;
}


void Scheme::UpdateFromTransactions()
{
    m_AmtInvested = 0;
    m_AverageNAV = 0;
    m_CAGR = 0;
    m_CurrMarketValue = 0;
    m_Gain = 0;
    m_TotalUnits = 0;

    xirrTransaction xtranLatest;

    for(int ii=0; ii < m_Transactions.count(); ii++)
    {
        m_AmtInvested += m_Transactions[ii].GetAmount();
        m_TotalUnits  += m_Transactions[ii].GetUnits();
        m_AverageNAV  += m_Transactions[ii].GetNAV();
    }
    m_AverageNAV = m_AverageNAV/m_Transactions.size() ;
    m_CurrMarketValue = m_TotalUnits * m_NAV;

    xirrTransactions xirrTransList = getxirrTransactions();

    xtranLatest.amount = 0-m_CurrMarketValue;
    xtranLatest.date = m_NAVDate;
    xirrTransList << xtranLatest;

    m_Gain = m_CurrMarketValue - m_AmtInvested;

    m_absReturn = (100*m_Gain)/m_AmtInvested;;
    m_CAGR = 0-CalculateXIRR(xirrTransList,0.01)*100;
}

void Scheme::ReadFromDB()
{
    QSqlQuery query;

    QString strTemp;

    strTemp = "%1%2";

    QString strQuery  = strTemp.arg("Select * from Transactions where SchemeCode=").arg(m_code);

    query.exec(strQuery);

    while(query.next())
    {
        QDate Date     = query.value(1).toDate();
        double amount  = query.value(2).toDouble();
        double nav 	   = query.value(3).toDouble();
        double units   = query.value(4).toDouble();

        Transaction trans(Date,amount,nav,units);
        m_Transactions.push_back(trans);
    }

    UpdateFromTransactions();
}

