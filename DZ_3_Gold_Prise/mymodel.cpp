#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QStandardItemModel{parent}
{

}

QVariant MyModel::data(const QModelIndex &index, int role) const // переопределяем метод data для выравнивания текста по центру
{
    if (role == Qt::TextAlignmentRole) {

        return Qt::AlignCenter;
    }

    return QStandardItemModel::data(index, role);
}
