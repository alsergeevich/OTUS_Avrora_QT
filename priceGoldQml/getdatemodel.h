#ifndef GETDATEMODEL_H
#define GETDATEMODEL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QStringList>

class GetDateModel : public QObject
{
    Q_OBJECT
public:
    GetDateModel(QObject *parent = nullptr);


public:
    QList<QStringList> getDate(QString path) const;
};

#endif // GETDATEMODEL_H
