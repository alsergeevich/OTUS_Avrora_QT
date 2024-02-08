#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QList>


//объявляем перечисление для добавления своих ролей
enum Roles {

    DateRole = 257,
    PurchaseRole,
    SellRole,
};


//объявляем структуру для создания объекта данных
struct Price {

    QString date;
    QString purchase;
    QString sell;
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QList<QStringList> &value);
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    //объявляем список для хранения объектов данных
    QList<Price> m_dateList;
};

#endif // TABLEMODEL_H
