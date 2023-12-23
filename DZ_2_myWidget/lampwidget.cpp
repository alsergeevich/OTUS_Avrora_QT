#include "lampwidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>


LampWidget::LampWidget(QWidget *parent, QColor on, QColor off, int m_radius) : QWidget{parent}, radius{m_radius} //в конструктор можно передать цвет вкл состояния, цвет выкл состояния, радиус
{
    colorDefaultOff = off;
    colorDefaultOn = on;
    xR = this->x();
    yR = this->y();
    this->setSize(radius*2);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


}



void LampWidget::setStatus() //метод где мы меняем состояние лампочки
{
    if(status == 0) {
        status = 1;
    }
    else {
        status = 0;
    }


    emit getStatus(status);
    repaint();
}

void LampWidget::paintEvent(QPaintEvent *event) //перерисовываем лампу в зависимости от состояния
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRadialGradient gradient;
    gradient.setFocalPoint(width()/2,height()/2);
    gradient.setCenter(width()/2,height()/2);
    gradient.setRadius(radius*2);


    if(status == 0) {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(0.5, colorDefaultOff);

        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(QBrush(gradient));
        painter.drawEllipse(xR, yR, width(),height());
    }

    if(status == 1) {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(0.6, colorDefaultOn);

        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(QBrush(gradient));
        painter.drawEllipse(xR, yR, width(),height());

    }

}

QSize LampWidget::sizeHint() const //возвращаем размеры для компоновщика
{
    return QSize(radius, radius);
}

int LampWidget::getStatusLamp() //получаем статус лампы
{
    return status;
}

void LampWidget::setStatusLamp(int s) //метод для изменения статуса лампы
{
    status = s;
    repaint();
}

void LampWidget::setSize(int radius) //метод для изменения размеров лампы
{
    this->setFixedWidth(radius);
    this->setFixedHeight(radius);
}

void LampWidget::mousePressEvent(QMouseEvent *event) //реакция лампы при клике по ней мыши
{
    if(status == 0) {
        status = 1;
    }
    else {
        status = 0;
    }


    emit getStatus(status);
    repaint();
}
