#ifndef MYMODEL_H
#define MYMODEL_H

#include <QStandardItemModel>
#include <QObject>

class MyModel : public QStandardItemModel // определяем свою модель наследуясь от QStandardItemModel для переопределения метода data
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    virtual QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MYMODEL_H
