#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include "mydelegatebacklight.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    csvModel = new MyModel(this); // создаём экземпляр модели
    csvModel->setColumnCount(3); // задаём количество столбцов
    csvModel->setHorizontalHeaderLabels(QStringList() << "Дата" << "Цена покупки" << "Цена продажи"); // задаём названия заголовков

    //настройки таблицы
    ui->tableView->setModel(csvModel); // задаём модель для tableView
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // растягиваем столбцы
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);


    ui->tableView->setItemDelegateForColumn(1, new MyDelegateBacklight(ui->tableView)); // задаём делегат для столбца 1
    ui->tableView->setItemDelegateForColumn(2, new MyDelegateBacklight(ui->tableView)); // задаём делегат для столбца 2

    // заполняем модель из файла
    QFile file(":/res/gold.csv"); // открываем файл с данными

    if (file.open(QIODevice::ReadOnly)) {

        int lineIndex = 0;
        QTextStream in (&file);

        while( !in.atEnd() ) {

            QString fileLine = in.readLine(); // читаем одну строку

            QStringList line = fileLine.split(","); // парсим строку по разделителю ","

            //записываем подготовленную строку в модель
            for( int i = 0; i < line.size(); ++i ) {

                QString str = line.at(i);
                QStandardItem *item = new QStandardItem(str);
                csvModel->setItem(lineIndex, i, item);
            }

            lineIndex++;
        }

        file.close();

        csvModel->removeRows(0,1); //удаляем строку с надписями столбцов из модели
    }



}

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}

