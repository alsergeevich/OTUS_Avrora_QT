#include "getdatemodel.h"

GetDateModel::GetDateModel(QObject *parent) : QObject { parent }
{

}


QList<QStringList> GetDateModel::getDate(QString path) const
{
    QList<QStringList> strList;

    QFile file(path); // открываем файл с данными

    if (file.open(QIODevice::ReadOnly)) {

        QTextStream in (&file);

        while( !in.atEnd() ) {

            QString fileLine = in.readLine(); // читаем одну строку
            QStringList line = fileLine.split(",");   // парсим строку по разделителю ","
            strList.append(line);
        }

        file.close();

        strList.pop_front();
    }

    return strList;
}
