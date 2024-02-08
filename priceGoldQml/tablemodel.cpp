#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}



int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_dateList.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return roleNames().size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = role;

    //в зависимости от роли возвращаем данные
    switch (col) {

    case DateRole:
        return m_dateList.at(row).date;

    case PurchaseRole:
        if (row == 0)
            return "*" + m_dateList.at(row).purchase;

        //вычисляем движение цены и возвращаем значение с меткой по которой потом узнаем какую иконку установить
        if (m_dateList.at(row).purchase.toDouble() - m_dateList.at(row-1).purchase.toDouble() > 0)
            return "+" + m_dateList.at(row).purchase;
        if (m_dateList.at(row).purchase.toDouble() - m_dateList.at(row-1).purchase.toDouble() < 0)
            return "-" + m_dateList.at(row).purchase;
        if (m_dateList.at(row).purchase.toDouble() - m_dateList.at(row-1).purchase.toDouble() == 0)
            return "*" + m_dateList.at(row).purchase;

    case SellRole:
        if (row == 0)
            return "*" + m_dateList.at(row).sell;

        //вычисляем движение цены и возвращаем значение с меткой по которой потом узнаем какую иконку установить
        if (m_dateList.at(row).sell.toDouble() - m_dateList.at(row-1).sell.toDouble() > 0)
            return "+" + m_dateList.at(row).sell;
        if (m_dateList.at(row).sell.toDouble() - m_dateList.at(row-1).sell.toDouble() < 0)
            return "-" + m_dateList.at(row).sell;
        if (m_dateList.at(row).sell.toDouble() - m_dateList.at(row-1).sell.toDouble() == 0)
            return "*" + m_dateList.at(row).sell;


    }

    return QVariant();
}

//заполняем модель данными
bool TableModel::setData(const QList<QStringList> &value)
{
    foreach (QStringList line, value) {
        m_dateList.append({line.at(0), line.at(1), line.at(2)});
    }

    return true;
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();

    //добавляем свои роли
    roles.insert(DateRole, "date");
    roles.insert(PurchaseRole, "purchase");
    roles.insert(SellRole, "sell");


    return roles;
}
