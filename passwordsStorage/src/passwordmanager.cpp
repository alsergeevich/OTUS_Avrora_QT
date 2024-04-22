#include "passwordmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

PasswordModel::PasswordModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int PasswordModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_data.size();
}

QVariant PasswordModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const QVariant &record = m_data[index.row()];
    if (role == Qt::DisplayRole) {
        return record;
    }
    return QVariant();
}

QHash<int, QByteArray> PasswordModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "recordData";
    roles[Qt::UserRole] = "recordId";
    return roles;
}

QList<QVariant> &PasswordModel::setQuery(QSqlQuery &query)
{
    beginResetModel();
    m_data.clear();
    while (query.next()) {
        QStringList record;
        record << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
        m_data.append(record);
    }
    endResetModel();
    return m_data;
}

void PasswordModel::clearModel()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}




PasswordManager::PasswordManager(QObject *parent) : QObject(parent)
{
    backend = new Backend;

    dbDirPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    dbaseName = QDir(dbDirPath).absoluteFilePath(DBNAME);

    if (!QDir().exists(dbDirPath)) {
        qInfo() << "Create new folder: " << dbDirPath;
        QDir().mkdir(dbDirPath);
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbaseName);
    if (!db.open()) {
        qDebug() << "Error connect to Database: " << db.lastError().text();
    }
    else {
        createTables();

    }
}

PasswordManager::~PasswordManager()
{
    qDebug() << "Delete";
    db.close();
}


void PasswordManager::createTables()
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS passwords (id INTEGER PRIMARY KEY, url TEXT, login TEXT, password TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS encryption_keys (id INTEGER PRIMARY KEY, key_value TEXT)");
}

bool PasswordManager::insertRecord(const QString &url, const QString &login, const QString &password)
{
//    qDebug() << getEncryptionKey();
    QString encryptPassword = backend->encrypt(password, getEncryptionKey());
//    qDebug() << encryptPassword;
    QSqlQuery query(db);
    query.prepare("INSERT INTO passwords (url, login, password) VALUES (?, ?, ?)");
    query.addBindValue(url);
    query.addBindValue(login);
    query.addBindValue(encryptPassword);
    if(query.exec()) {
        m_model.clearModel();
        QSqlQuery selectQuery("SELECT id, url, login, password FROM passwords", db);
        m_model.setQuery(selectQuery);
        emit modelChanged();
        return true;
    }
    return false;
}

bool PasswordManager::updateRecord(int id, const QString &url, const QString &login, const QString &password)
{
    QString encryptPassword = backend->encrypt(password, getEncryptionKey());
    QSqlQuery query(db);
    query.prepare("UPDATE passwords SET url = ?, login = ?, password = ? WHERE id = ?");
    query.addBindValue(url);
    query.addBindValue(login);
    query.addBindValue(encryptPassword);
    query.addBindValue(id);
    if(query.exec()) {
        m_model.clearModel();
        QSqlQuery selectQuery("SELECT id, url, login, password FROM passwords", db);
        m_model.setQuery(selectQuery);
        emit modelChanged();
        return true;
    }
    return false;
}

bool PasswordManager::deleteRecord(int id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM passwords WHERE id = ?");
    query.addBindValue(id);
    if(query.exec()) {
        m_model.clearModel();
        QSqlQuery selectQuery("SELECT id, url, login, password FROM passwords", db);
        m_model.setQuery(selectQuery);
        emit modelChanged();
        return true;
    }
    return false;
}

QList<QVariant> PasswordManager::getRecords()
{
    m_model.clearModel();
    QSqlQuery selectQuery("SELECT id, url, login, password FROM passwords", db);
    //m_model.setQuery(selectQuery);
    return m_model.setQuery(selectQuery);
}

PasswordModel *PasswordManager::searchRecords(const QString &searchTerm)
{
//    auto *model = new QSqlQueryModel(this);
    QSqlQuery query(db);
    query.prepare("SELECT id, url, login, password FROM passwords WHERE url LIKE ? OR login LIKE ?");
    query.addBindValue('%' + searchTerm + '%');
    query.exec();
    m_model.setQuery(query);
    emit modelChanged();
    return &m_model;
}

bool PasswordManager::saveEncryptionKey(const QString &key)
{
    QString encryptPassword = backend->hash(key);
    QSqlQuery query(db);
    query.prepare("INSERT INTO encryption_keys (key_value) VALUES (?)");
    query.addBindValue(encryptPassword);
    return query.exec();
}

QString PasswordManager::getEncryptionKey()
{
    QSqlQuery query(db);
    query.exec("SELECT key_value FROM encryption_keys ORDER BY id DESC LIMIT 1"); //получаем самую последнюю запись
    if (query.next()) {
        return query.value(0).toString();
    }
    return "";
}

bool PasswordManager::isFirstRun()
{
    QSqlQuery query(db);
    query.exec("SELECT COUNT(*) FROM encryption_keys");

    if (query.next()) {
            return query.value(0).toInt() == 0;
        }

    return true;
}

void PasswordManager::dropTable()
{
    QSqlQuery query(db);
    query.exec("DROP TABLE IF EXISTS passwords");
    query.exec("DROP TABLE IF EXISTS encryption_keys");
}

bool PasswordManager::comparePasswords(QString passw)
{
    QString savePassw = getEncryptionKey();
    QString inputPassw = backend->hash(passw);
    return savePassw == inputPassw;
}



PasswordModel *PasswordManager::getModel()
{
    return &m_model;
}

QString PasswordManager::getDecriptionPassword(QString password, QString key)
{
//    qDebug() << password;
//    qDebug() << key;
//    qDebug() << backend->decrypt(password, key);
    return backend->decrypt(password, key);
}


