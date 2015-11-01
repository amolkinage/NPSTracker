#include "npsmodel.h"



NPSModel::NPSModel(QObject *parent)
    : QAbstractListModel(parent)
{

}


void NPSModel::addPortfolio(const Portfolio *portolio)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Portfolios << (Portfolio*)portolio;
    endInsertRows();
}

int NPSModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_Portfolios.count();
}

QVariant NPSModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_Portfolios.count())
        return QVariant();

    const Portfolio *portfolio = m_Portfolios[index.row()];
    switch(role)
    {
    case PortfolioName:
        return portfolio->getName();
        break;
    case PortfolioMarketValue:
    {
        QString value = QString("%L1").arg(portfolio->getMarketValue(),0,'f',2);
        return value;
        break;
    }
    case PortfolioId:
        return portfolio->getCode();
        break;
    case PortfolioInvestValue:
    {
        QString value = QString("%L1").arg(portfolio->getInvestValue(),0,'f',2);
        return value;
        break;
    }
    case PortfolioCAGR:
    {
        QString value;

        if(0 > portfolio->getCAGR())
        {
            value =  QString("%1").arg(portfolio->getCAGR(),0,'f',2);
        }
        else
        {
            value = QString("+%1").arg(portfolio->getCAGR(),0,'f',2);
        }
        return value;
        break;
    }
    case PortfolioReturn:
    {
        QString value;
        if(0 > portfolio->getReturns())
        {
            value = QString("%1").arg(portfolio->getReturns(),0,'f',2);
        }
        else
        {
            value = QString("+%1").arg(portfolio->getReturns(),0,'f',2);
        }

        return value;
        break;
    }
    default:
        return QVariant();
    }

    return QVariant();
}

//![0]
QHash<int, QByteArray> NPSModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PortfolioName] = "PortfolioName";
    roles[PortfolioMarketValue] = "PortfolioMarketValue";
    roles[PortfolioId] = "PorfolioId";
    roles[PortfolioInvestValue]="PortfolioInvestValue";
    roles[PortfolioCAGR]="PortfolioCAGR";
    roles[PortfolioReturn]="PortfolioReturn";

    return roles;
}

void NPSModel::ReadfromDB(QSqlDatabase &gdbNPS)
{
    Q_UNUSED(gdbNPS);

    QSqlQuery query;

    query.exec("Select * from portfolio");

    while(query.next())
    {
        QString name = query.value(0).toString();
        int     Code = query.value(1).toInt();

        Portfolio *portf = new Portfolio();//(name,Code);
        portf->SetName(name);
        portf->SetCode(Code);

        addPortfolio(portf);
    }

    for(int i=0; i<m_Portfolios.count();i++)
    {
        m_Portfolios[i]->ReadFromDB();
    }
}
