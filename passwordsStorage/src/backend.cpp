#include "backend.h"
#include "xtea.h"
#include <QCryptographicHash>


Backend::Backend(QObject *parent)
    : QObject{parent}
{}

Backend::~Backend()
{

}

QString Backend::hash(const QString &data) {
    return QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Md5).toBase64();
}

QString Backend::encrypt(const QString &data, const QString &key) {
    QByteArray out = data.toUtf8();
    Xtea xtea(32);
    xtea.Encrypt(out, QByteArray::fromBase64(key.toUtf8()));
    return out.toBase64();
}

QString Backend::decrypt(const QString &data, const QString &key) {
    QByteArray out = QByteArray::fromBase64(data.toUtf8());
    Xtea xtea(32);
    xtea.Decrypt(out, QByteArray::fromBase64(key.toUtf8()));
    return out;
}
