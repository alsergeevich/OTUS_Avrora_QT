#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPixmap>
#include <QMap>
#include "getweathercity.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:

    void on_pushButton_clicked();
    void getCoordinats(double lat, double lon);
    void getWeather(const CurrentWeather &cw);

private:

    Ui::Widget *ui;
    QMap<QString, QString> descriptionMap; //словарь для перевода описаний погоды с английского на русский


};
#endif // WIDGET_H
