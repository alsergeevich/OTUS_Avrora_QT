#ifndef GETCOORDINATSCITY_H
#define GETCOORDINATSCITY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QUrl>
#include <QDebug>



class GetCoordinatsCity : public QObject
{
    Q_OBJECT
public:
    explicit GetCoordinatsCity(const QString &cityName, QObject *parent = nullptr);
    ~GetCoordinatsCity();

public:


private slots:
    void _onResults(QNetworkReply *reply); //слот для обработки результатов запроса

signals:
    void finishWork (double lat, double lon); // сигнал который испускается по окончанию обработки запроса

private:

    QNetworkAccessManager *networkManager;
    QString _fullQuery;
    QString _templateQueryFirst = "http://api.openweathermap.org/geo/1.0/direct?q=";
    QString _templateQueryAfterCity = "&limit=1&appid=";
    QString _city;
    QString _api_key = "";
    double _lat {0};
    double _lon {0};


};

#endif // GETCOORDINATSCITY_H
