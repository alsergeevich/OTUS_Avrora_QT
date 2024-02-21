#include "getweathercity.h"

GetWeatherCity::GetWeatherCity(double lat, double lon, QObject *parent)
    : QObject{parent}, _lat{lat}, _lon{lon}
{


    networkManager = new QNetworkAccessManager();
    _fullQuery = _templateQueryFirst + QString::number(_lat) + _templateQueryAfterLat + QString::number(_lon) + _api_key;

    // если проблемы с ssl то в консоль выдаст инфу об этом
    if (!QSslSocket::supportsSsl()) {
        qDebug() << "QSslSocket::sslLibraryBuildVersionString()" << QSslSocket::sslLibraryBuildVersionString();
        qDebug() << "Supports SSL: " << QSslSocket::supportsSsl();
    }

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_onResults(QNetworkReply*))); //подключаемся к сигналу об окончании запроса
    request.setUrl(QUrl(_fullQuery));
    networkManager->get(request);

}

GetWeatherCity::~GetWeatherCity()
{

}

//разбираем JSON файл
void GetWeatherCity::_onResults(QNetworkReply *reply)
{
    if (!reply->error()) {

        CurrentWeather currentWeather;
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root_obj = document.object();
        QJsonValue jsVal = root_obj.value("weather"); //ищем объект weather
        QJsonArray jsArray = jsVal.toArray(); //получаем его значение массив
        QJsonObject o = jsArray.at(0).toObject(); //преобразуем значение массива в объект

        QVariantMap root_map = root_obj.toVariantMap();
        QVariantMap weather_map = root_map["main"].toMap();
        QVariantMap wind_map = root_map["wind"].toMap();

        CurrentWeather cw; //создаём объек структуры погоды
        //заполняем структуру данными
        cw.weather_description = o.value("description").toString(); //получаем описание погоды
        cw.weather_icon = o.value("icon").toString(); //получаем иконку
        cw.city_name = root_map["name"].toString();

        cw.main_temp = weather_map["temp"].toDouble() - 273;
        cw.main_feels_like = weather_map["feels_like"].toDouble() - 273;
        cw.main_temp_min = weather_map["temp_min"].toDouble() - 273;
        cw.main_temp_max = weather_map["temp_max"].toDouble() - 273;
        cw.main_pressure = weather_map["pressure"].toDouble();
        cw.main_humidity = weather_map["humidity"].toDouble();
        cw.wind_speed = wind_map["speed"].toDouble();

        emit endOfRequestProcessing(cw); //испускаем сигнал и передаём структуру с данными дальше



    }

}
