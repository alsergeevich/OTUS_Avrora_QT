#include "getcoordinatscity.h"

GetCoordinatsCity::GetCoordinatsCity(const QString &cityName, QObject *parent)
    : QObject{parent}, _city {cityName}
{
    networkManager = new QNetworkAccessManager();
    _fullQuery = _templateQueryFirst + _city + _templateQueryAfterCity + _api_key; //формируем запрос координат по названию города
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_onResults(QNetworkReply*))); //подключаемся к сигналу об окончании запроса
    networkManager->get(QNetworkRequest(QUrl(_fullQuery)));
}

GetCoordinatsCity::~GetCoordinatsCity()
{

}


//обрабатываем результаты запроса
void GetCoordinatsCity::_onResults(QNetworkReply *reply)
{
    if (!reply->error()) {

        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        if ( document.isArray()) {
            QJsonArray arrayDoc = document.array();
            QJsonObject o = arrayDoc.at(0).toObject();
            _lat = o.value("lat").toDouble(); //получаем широту
            // qDebug() << _lat;
            _lon = o.value("lon").toDouble(); //получаем долготу
            // qDebug() << _lon;

            emit finishWork(_lat, _lon); //испускаем сигнал в котором передаём результаты обработки JSON в виде координат
        }

    }

}
