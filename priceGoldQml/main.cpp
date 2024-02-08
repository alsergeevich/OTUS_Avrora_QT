#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tablemodel.h"
#include "getdatemodel.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    TableModel *myModel = new TableModel;
    GetDateModel dateModel;

    QList<QStringList> dates = dateModel.getDate(":/dataFile/gold.csv"); //получаем данные из файла
    myModel->setData(dates); //отправляем данные в модель


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("myModel", myModel);
    engine.load(url);

    return app.exec();
}
