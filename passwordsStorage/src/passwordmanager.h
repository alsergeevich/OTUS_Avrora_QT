#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "backend.h"
#include <QAbstractListModel>


class PasswordModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PasswordModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<QVariant>& setQuery(QSqlQuery &query);
    void clearModel();

private:
    QList<QVariant> m_data; // Data storage for the model
};



class PasswordManager : public QObject
{
    Q_OBJECT


public:
    explicit PasswordManager(QObject *parent = nullptr);
    ~PasswordManager();

    Q_INVOKABLE bool insertRecord(const QString &url, const QString &login, const QString &password);
    Q_INVOKABLE bool updateRecord(int id, const QString &url, const QString &login, const QString &password);
    Q_INVOKABLE bool deleteRecord(int id);
    Q_INVOKABLE QList<QVariant> getRecords();
    Q_INVOKABLE PasswordModel *searchRecords(const QString &searchTerm);
    Q_INVOKABLE bool saveEncryptionKey(const QString &key);
    Q_INVOKABLE QString getEncryptionKey();
    Q_INVOKABLE bool isFirstRun();
    Q_INVOKABLE void dropTable();
    Q_INVOKABLE bool comparePasswords(QString passw);
    Q_INVOKABLE PasswordModel *getModel();
    Q_INVOKABLE QString getDecriptionPassword(QString password, QString key);


private:
     QSqlDatabase db;
     void createTables();
     Backend* backend;
     QString dbDirPath;
     QString dbaseName;
     const QString DBNAME = "passwords.db";
     PasswordModel m_model;


signals:
     void modelChanged();
};

#endif // PASSWORDMANAGER_H
