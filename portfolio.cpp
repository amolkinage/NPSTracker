#include "portfolio.h"
#include <QtSql>
#include <QDate>

Portfolio::Portfolio(QObject *parent): QAbstractListModel(parent)
{
    m_Code = 0;
    m_AmountInvested = 0;
    m_MarketValue = 0;
    m_Gain = 0;
    m_CAGR = 0;
}

void Portfolio::addScheme(const Scheme &scheme)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Schemes << scheme;
    endInsertRows();
}

int Portfolio::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_Schemes.count();
}

QVariant Portfolio::data(const QModelIndex & index, int role) const {
    //qDebug() << "Index" << index.row();

    if (index.row() < 0 || index.row() >= m_Schemes.count())
        return QVariant();

    const Scheme &scheme = m_Schemes[index.row()];

    switch(role)
    {
    case SchemeName:
        return scheme.getName();
        break;
    case SchemeMarketValue:
    {
        QString value = QString("%L1").arg(scheme.getMarketValue(),0,'f',2);
        return value;
    }
        break;
    case SchemeId:
        return scheme.getCode();
        break;
    case SchemeInvestValue:
    {
        QString value = QString("%L1").arg(scheme.getAmoutInvested(),0,'f',2);
        return value;
    }
        break;
    case SchemeCAGR:
    {
        QString value;

        if(0 > scheme.getCAGR())
        {
            value =  QString("%1").arg(scheme.getCAGR(),0,'f',2);
        }
        else
        {
            value = QString("+%1").arg(scheme.getCAGR(),0,'f',2);
        }
        return value;
    }
        break;
    case SchemeReturns:
    {
        QString value;
        if(0 > scheme.getGain())
        {
            value = QString("%1").arg(scheme.getReturns(),0,'f',2);
        }
        else
        {
            value = QString("+%1").arg(scheme.getReturns(),0,'f',2);
        }

        return value;
    }
        break;
    default:
        return QVariant();
    }

    return QVariant();
}

//![0]
QHash<int, QByteArray> Portfolio::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[SchemeName] = "SchemeName";
    roles[SchemeMarketValue] = "SchemeMarketValue";
    roles[SchemeId] = "SchemeId";
    roles[SchemeCAGR] = "SchemeCAGR";
    roles[SchemeInvestValue]= "SchemeInvestValue";
    roles[SchemeReturns]="SchemeReturns";
    return roles;
}

void Portfolio::ReadFromDB()
{
    QSqlQuery query;

    QString strTemp;

    strTemp = "%1%2";
    QString strQuery = strTemp.arg("Select * from Schemes where PortfolioCode=").arg(m_Code);


    query.exec(strQuery);

    while(query.next())
    {
        QString name = query.value(0).toString();
        int  Code	 = query.value(1).toInt();
        double nav 	 = query.value(3).toDouble();
        QDate  navdate = query.value(6).toDate();

        Scheme sch(name,Code,nav,navdate);
        addScheme(sch);
    }

    for(int i=0; i<m_Schemes.count();i++)
    {
        m_Schemes[i].ReadFromDB();
        m_AmountInvested += m_Schemes[i].getAmoutInvested();
        m_MarketValue += m_Schemes[i].getMarketValue();
        m_Gain += m_Schemes[i].getGain();

        m_xirrTransactions.append(m_Schemes[i].getxirrTransactions());
    }
    m_absReturn = (100*m_Gain)/m_AmountInvested;

    xirrTransaction xtranLatest;
    xtranLatest.amount = 0-m_MarketValue;
    xtranLatest.date = QDate::currentDate();
    m_xirrTransactions << xtranLatest;

    m_CAGR = 0- CalculateXIRR(m_xirrTransactions,m_absReturn)*100;
}

void Portfolio::SetName(QString name)
{
    m_Name = name;
}


void Portfolio::SetCode(int code)
{
    m_Code = code;
}
