//
// Created by Administrator on 2016/9/11.
//

#include "Observer.h"

Observer::Observer(Observable *o):ob(o) {
    ob->addObserver(this);
}

void WeatherNews::update
        (double temperature, double humidity, double pressure){
    this->temperature = temperature;
    this->humidity = humidity;
}

void WeatherNews::display() {
    std::cout << "today's temperature is "
              << this->temperature << ", "
              <<"and humidity is " << this->humidity << endl;
}

void WeatherForecast::update(double temperature, double humidity, double pressure) {
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
}

void WeatherForecast::display() {
    std::cout << "we don't do weather report"
            " but we do Forecast" <<endl;
    foreCast();
}

void WeatherForecast::foreCast() {
    std::cout << "tomorrow temperature : " << this->temperature + 50 << endl;
}
