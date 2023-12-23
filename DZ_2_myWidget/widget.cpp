#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnOnOff, SIGNAL(clicked(bool)), ui->lamp, SLOT(setStatus()));



}

Widget::~Widget()
{
    delete ui;

}

