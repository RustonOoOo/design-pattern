//
// Created by Administrator on 2016/9/11.
//

#ifndef DESIGNPATTERN_OBSERVABLE_H
#define DESIGNPATTERN_OBSERVABLE_H

#include "Observer.h"
#include <vector>
using namespace std;
class Observer;
class Observable {//观察者所观察的对象
private:
    double temperature;
    double humidity;
    double pressure;
    void setChange() {change = true;}
    vector<Observer*> obs;
    bool change;
public:
    void setData(double temperature, double humidity, double pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
    }
    void addObserver(Observer* observer);
    void deleteObserver(Observer* observer){
        auto positon = std::find(obs.begin(), obs.end(), observer);
        obs.erase(positon);
    }
    void notifyDataChanged();
};





class WeatherData : public Observable {//天气为所观察的对象
protected:
    double temperature;
    double humidity;
    double pressure;
public:
    double getTemperature();
    double getHumidity();
    double getPressure();
};
#endif //DESIGNPATTERN_OBSERVABLE_H
