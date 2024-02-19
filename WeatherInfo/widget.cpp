#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "getcoordinatscity.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //формируем словарь для перевода английских описаний
    descriptionMap["clear sky"] = "Ясное небо";
    descriptionMap["few clouds"] = "Небольшая облачность";
    descriptionMap["scattered clouds"] = "Рассеянные облака";
    descriptionMap["broken clouds"] = "Разорванные облака";
    descriptionMap["shower rain"] = "Ливень";
    descriptionMap["rain"] = "Дождь";
    descriptionMap["thunderstorm"] = "Гроза";
    descriptionMap["snow"] = "Снег";
    descriptionMap["mist"] = "Туман";
    descriptionMap["overcast clouds"] = "Сплошная облачность";

    descriptionMap["thunderstorm with light rain"] = "Гроза, слабый дождь";
    descriptionMap["thunderstorm with rain"] = "Гроза с дождём";
    descriptionMap["thunderstorm with rain"] = "Гроза, сильный дождь";
    descriptionMap["light thunderstorm"] = "Лёгкая гроза";
    descriptionMap["heavy thunderstorm"] = "Сильная гроза";
    descriptionMap["ragged thunderstorm"] = "Рваная гроза";
    descriptionMap["thunderstorm with light drizzle"] = "Гроза, моросящий дождь";
    descriptionMap["thunderstorm with drizzle"] = "Гроза, моросящий дождь";
    descriptionMap["thunderstorm with heavy drizzle"] = "Гроза, сильный моросящий дождь";

    descriptionMap["light intensity drizzle"] = "Слабый моросящий дождь";
    descriptionMap["drizzle"] = "Мелкий дождь";
    descriptionMap["heavy intensity drizzle"] = "Сильный моросящий дождь";
    descriptionMap["light intensity drizzle rain"] = "Слабый моросящий дождь";
    descriptionMap["drizzle rain"] = "Моросящий дождь";
    descriptionMap["heavy intensity drizzle rain"] = "Сильный моросящий дождь";
    descriptionMap["shower rain and drizzle"] = "Дождь и морось";
    descriptionMap["heavy shower rain and drizzle"] = "Сильный ливень и морось";
    descriptionMap["shower drizzle"] = "Моросящий дождь";

    descriptionMap["light rain"] = "Небольшой дождь";
    descriptionMap["moderate rain"] = "Умеренный дождь";
    descriptionMap["heavy intensity rain"] = "Сильный дождь";
    descriptionMap["very heavy rain"] = "Очень сильный дождь";
    descriptionMap["extreme rain"] = "Сильный дождь";
    descriptionMap["freezing rain"] = "Ледяной дождь";
    descriptionMap["light intensity shower rain"] = "Лёгкий дождь";
    descriptionMap["heavy intensity shower rain"] = "Сильный ливень";
    descriptionMap["ragged shower rain"] = "Рваный ливень";

    descriptionMap["light snow"] = "Небольшой снег";
    descriptionMap["heavy snow"] = "Сильный снегопад";
    descriptionMap["sleet"] = "Мокрый снег";
    descriptionMap["light shower sleet"] = "Небольшой дождь с мокрым снегом";
    descriptionMap["shower sleet"] = "Ливень с мокрым снегом";
    descriptionMap["light rain and snow"] = "Небольшой дождь и снег";
    descriptionMap["rain and snow"] = "Дождь и снег";
    descriptionMap["shower snow"] = "Сильный снегопад";
    descriptionMap["heavy shower snow"] = "Сильный снегопад";
    descriptionMap["light shower snow"] = "Лёгкий дождь со снегом";

    descriptionMap["smoke"] = "Дым";
    descriptionMap["haze"] = "Мгла";
    descriptionMap["sand/dust whirls"] = "Песчаные вихри";
    descriptionMap["fog"] = "Туман";
    descriptionMap["sand"] = "Песок";
    descriptionMap["dust"] = "Пыль";
    descriptionMap["volcanic ash"] = "Вулканический пепел";
    descriptionMap["squalls"] = "Шквал";
    descriptionMap["tornado"] = "Торнадо";


}

Widget::~Widget()
{
    delete ui;
}





void Widget::on_pushButton_clicked()
{
    if (ui->lineEditCity->text() != "") {
        //получаем координаты города
        GetCoordinatsCity *getCoordinats = new GetCoordinatsCity(ui->lineEditCity->text());

        //подключаемся к сигналу об окончании обработки запроса в котором получаем координаты
        connect(getCoordinats, SIGNAL(finishWork(double,double)), this, SLOT(getCoordinats(double,double)));
    }
    return;
}

void Widget::getCoordinats(double lat, double lon)
{
    //выводим координаты
    ui->labelLat->setText(QString::number(lat));
    ui->labelLon->setText(QString::number(lon));

    //передаём координаты в класс для получения погоды
    GetWeatherCity *weather = new GetWeatherCity(lat, lon);
    //подключаемся к сигналу об окончании обработки запроса и получаем структуру с данными о погоде
    connect(weather, SIGNAL(endOfRequestProcessing(CurrentWeather)), this, SLOT(getWeather(CurrentWeather)));

}

//метод слот для обработки данных по погоде
void Widget::getWeather(const CurrentWeather &cw)
{

    QPixmap pix(":/weather/" + cw.weather_icon + ".png"); //устанавливаем иконку погоды

    //заполняем данными интерфейс
    ui->labelNameCity->setText(cw.city_name);
    ui->labelIcon->setPixmap(pix);
    ui->labelTemperature->setText(QString::number(cw.main_temp) + "°" + "C");
    ui->labelDescriptions->setText(descriptionMap[cw.weather_description]);
    ui->labelFeels_like->setText("Ощущается как:     " + QString::number(cw.main_feels_like) + "°" + "C");
    ui->labelTemp_min->setText("Мин.температура: " + QString::number(cw.main_temp_min) + "°" + "C");
    ui->labelTemp_max->setText("Макс.температура: " + QString::number(cw.main_temp_max) + "°" + "C");
    ui->labelPressure->setText("Давление:  " + QString::number(cw.main_pressure) + "hPa");
    ui->labelHumidity->setText("Влажность: " + QString::number(cw.main_humidity) + "%");
    ui->labelWindSpeed->setText("Ветер:         " + QString::number(cw.wind_speed) + "м/с");

}

