#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QAction>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QAction* clearAction = ui->lineEdit->findChild<QAction*> (); //добавляем кнопке удалить в текстовом поле действие очистить
    if(clearAction){
        clearAction->setEnabled (true);
    }
    ui->lineEdit->setMinimumSize (150, 50);
    ui->lineEdit->addAction (clearAction);
    connect (clearAction, &QAction::triggered, ui->lineEdit, [this](){on_pushButton_16_clicked();});


}

Widget::~Widget()
{
    delete ui;
}

void Widget::calculate() //функция расчёта
{
    qreal fOperand2 = m_stk.pop ().toFloat (); //берём из стека значение 2
    QString strOperation = m_stk.pop (); //берём из стека знак операции
    qreal fOperand1 = m_stk.pop ().toFloat (); //берём из стека значение 1
    qreal fResult = 0;

    if(strOperation == "+"){
        fResult = fOperand1 + fOperand2;
    }

    if(strOperation == "-"){
        fResult = fOperand1 - fOperand2;
    }

    if(strOperation == "*"){
        fResult = fOperand1 * fOperand2;
    }

    if(strOperation == "/"){
        if(fOperand2 == 0){
            QMessageBox::information (this, "Деление на ноль !", "Деление на ноль невозможно !"); //обрабатываем ситуацию деления на ноль
            ui->lineEdit->clear ();
            m_stk.clear ();
            str = "";
            return;
        }
        else {
            fResult = fOperand1 / fOperand2;
        }
    }

    ui->lineEdit->setText (QString().setNum (fResult));
}

void Widget::checkStack(QString & s) //функция проверки содержимого стека
{
    if(m_stk.count () >= 2) {
        m_stk.push (ui->lineEdit->text ());
        calculate ();
        m_stk.clear ();
        m_stk.push (ui->lineEdit->text ());
        if(s != "=") {
            m_stk.push (s);
            str = "";
        }
    }
    else {
        m_stk.push (ui->lineEdit->text ());
        m_stk.push (s);
        str = "";
        flagPoint = false;
    }
}










void Widget::on_pushButton_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_17_clicked()
{
    if(ui->lineEdit->text () != "" && !(flagPoint)) { //проверяем, чтобы точку не нажали в начале и не смогли ввести ее больше одного раза в каждом числе

        flagPoint = true;
        str += ((QPushButton*)sender ())->text ();
        ui->lineEdit->setText (str);

    }
    else {
        return;
    }
}


void Widget::on_pushButton_2_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_3_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_4_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_5_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_6_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_7_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_8_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_9_clicked()
{
    str += ((QPushButton*)sender ())->text ();
    ui->lineEdit->setText (str);
}


void Widget::on_pushButton_10_clicked()
{
    if(str == ""){
        return;
    }
    else {
        if(str[0] == '0' && str.length () <= 1){
            return;
        }
        else {
            str += ((QPushButton*)sender ())->text ();
            ui->lineEdit->setText (str);
        }
    }
}


void Widget::on_pushButton_11_clicked()
{
    QString op = ((QPushButton*)sender ())->text ();

    checkStack (op);
}


void Widget::on_pushButton_12_clicked()
{
    QString op = ((QPushButton*)sender ())->text ();
    checkStack (op);
}


void Widget::on_pushButton_13_clicked()
{
    QString op = ((QPushButton*)sender ())->text ();
    checkStack (op);
}


void Widget::on_pushButton_14_clicked()
{
    QString op = ((QPushButton*)sender ())->text ();
    checkStack (op);
}


void Widget::on_pushButton_15_clicked()
{
    QString op = ((QPushButton*)sender ())->text ();
    checkStack (op);
}


void Widget::on_pushButton_16_clicked()
{
    m_stk.clear ();
    ui->lineEdit->setText ("");
    str = "";
    return;
}

