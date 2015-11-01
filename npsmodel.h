#ifndef NPSMODEL_H
#define NPSMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QtSql>
#include "portfolio.h"


class NPSModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum NPSRoles {
        PortfolioName = Qt::UserRole + 1,
        PortfolioMarketValue,
        PortfolioId,
        PortfolioInvestValue,
        PortfolioCAGR,
        PortfolioReturn
    };
    NPSModel(QObject *parent = 0);

    void addPortfolio(const Portfolio *portolio );
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void ReadfromDB(QSqlDatabase &gdbNPS);

    Q_INVOKABLE int getPorfolioId(int index)
    {
        //return 0;
        return m_Portfolios[index]->getCode();
    }

    Q_INVOKABLE QObject* getSchemeModel(int index)
    {
        //qDebug() << "Returning model for "<<index<<m_Portfolios[index]->getName();
        return (QObject*) m_Portfolios[index];
    }
    Q_INVOKABLE QObject* getPorfolioModel()
    {
        //qDebug() << "Returning Porfolio Model ";
        return (QObject*) this;
    }

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Portfolio*> m_Portfolios;
};

#endif // NPSMODEL_H
