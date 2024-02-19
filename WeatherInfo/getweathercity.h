#ifndef GETWEATHERCITY_H
#define GETWEATHERCITY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QUrl>
#include <QSslConfiguration>
#include <QDebug>


struct CurrentWeather {

    QString weather_description;
    QString weather_icon;

    double main_temp;
    double main_feels_like;
    double main_temp_min;
    double main_temp_max;
    double main_pressure;
    double main_humidity;

    double wind_speed;
    QString city_name;
};

class GetWeatherCity : public QObject
{
    Q_OBJECT


public:
    explicit GetWeatherCity(double lat, double lon, QObject *parent = nullptr);
    ~GetWeatherCity();

private slots:
    void _onResults(QNetworkReply *reply); //слот для обработки результатов запроса

signals:
    void endOfRequestProcessing(const CurrentWeather &cw);

private:
    QNetworkAccessManager *networkManager;
    QNetworkRequest request;
    QString _fullQuery;
    const QString _templateQueryFirst = "https://api.openweathermap.org/data/2.5/weather?lat=";
    const QString _templateQueryAfterLat = "&lon=";
    double _lat;
    double _lon;
    const QString _api_key = "&appid=";





};

#endif // GETWEATHERCITY_H
