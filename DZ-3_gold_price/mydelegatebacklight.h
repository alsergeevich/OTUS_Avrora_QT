#ifndef MYDELEGATEBACKLIGHT_H
#define MYDELEGATEBACKLIGHT_H

#include <QStyledItemDelegate>
#include <QObject>

class MyDelegateBacklight : public QStyledItemDelegate
{
    Q_OBJECT

    using BaseClass = QStyledItemDelegate; // чтобы проще было писать :)

public:
    MyDelegateBacklight(QObject* parent = nullptr);

    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MYDELEGATEBACKLIGHT_H
