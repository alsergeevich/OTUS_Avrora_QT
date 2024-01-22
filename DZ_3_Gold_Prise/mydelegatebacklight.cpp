#include "mydelegatebacklight.h"
#include <QPainter>
#include <QDebug>
#include <QPixmap>

MyDelegateBacklight::MyDelegateBacklight(QObject *parent) : BaseClass(parent)
{

}

void MyDelegateBacklight::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    double priceCurrent {0}; // переменная для цены в текущей ячейке
    double priceOld {0}; // переменная для цены в предыдущей ячейке
    double result {0}; // переменная для разницы в цене
    QRect rec = option.rect; // получаем размеры ячейки
    QModelIndex oldIndex; // переменная для вычесления индекса верхней ячейки
    QPixmap icon; // переменная для иконки


    if (index.column() == 1 || index.column() == 2) {   // если стобец 1 или 2

//        if(index.row() == 0) {

//            return;
//        }

        priceCurrent = index.model()->data(index).toDouble(); // получаем цену в текущей ячейке
        oldIndex = index.sibling(index.row()-1, index.column()); // вычисляем индекс предыдущей ячейки
        priceOld = index.model()->data(oldIndex).toDouble(); // получаем цену в предыдущей ячейке
        result = priceCurrent - priceOld; // вычисляем направление цены

        painter->save();
        if (result > 0) { // если цена пошла вверх

            icon = QPixmap(":/uparrow.ico").scaled(15,15); // устанавливаем иконку стрелка вверх
        }
        else if (result < 0) { // если цена вниз

            icon = QPixmap(":/arrowdown.ico").scaled(15,15); // устанавливаем иконку стрелка вниз
        }
        else if (result == 0) { // если цена не изменилась

            icon = QPixmap(":/neutral_price.ico").scaled(15,15); // устанавливаем иконку квадрат
        }

        painter->drawPixmap(rec.x()+(rec.width()-15), rec.y()+(rec.height()), icon); // рисуем иконку
        painter->restore();

    }



    BaseClass::paint(painter,option,index); // иначе используем метод paint по умолчанию

}
