#include "myclass.h"

MyClass::MyClass(QObject *parent) : QObject(parent)
{

}

void MyClass::notification()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface i_bus("org.freedesktop.Notifications", "/org/freedesktop/Notifications", "org.freedesktop.Notifications", bus);
    QVariantList args;
    args << QString("");
    args << QVariant(QVariant::UInt);
    args << QVariant("");
    args << QString("Зачисление:");
    args << QString("100000 руб");
    args << QStringList();
    args << QVariantMap();
    args << -1;
    i_bus.callWithArgumentList(QDBus::AutoDetect, "Notify", args);


}
