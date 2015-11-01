#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <QAbstractListModel>
#include <QStringList>
#include "scheme.h"
#include "xirrtransaction.h"


class Portfolio : public QAbstractListModel
{
    Q_OBJECT

public:
    enum SchemeRoles {
        SchemeName = Qt::UserRole + 1,
        SchemeMarketValue,
        SchemeId,
        SchemeInvestValue,
        SchemeCAGR,
        SchemeReturns
    };
    Portfolio(QObject *parent = 0);
    //Portfolio(const QString name, int code,QObject *parent = 0);


    void addScheme(const Scheme &scheme );
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QString getName() const { return m_Name; }
    int     getCode() const { return m_Code; }
    double  getMarketValue() const { return m_MarketValue; }
    double  getInvestValue() const { return m_AmountInvested;}
    double  getCAGR() const { return m_CAGR;}
    double  getReturns() const { return m_absReturn;}

    void SetName(QString name);
    void SetCode(int code);
    void ReadFromDB();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QString m_Name;
    int     m_Code;
    double  m_AmountInvested;
    double  m_MarketValue;
    double  m_Gain;
    double  m_absReturn;
    double  m_CAGR;

    QList<Scheme> m_Schemes;
    QList<xirrTransaction> m_xirrTransactions;
};

#endif // PORTFOLIO_H
