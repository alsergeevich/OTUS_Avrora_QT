#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();
    Q_INVOKABLE QString hash    (const QString& data);
    Q_INVOKABLE QString encrypt(const QString& data, const QString& key);
    Q_INVOKABLE QString decrypt(const QString& data, const QString& key);

signals:
};

#endif // BACKEND_H
