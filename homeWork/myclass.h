#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
    Q_INVOKABLE void notification();

signals:

};

#endif // MYCLASS_H
