//
// Created by Administrator on 2016/9/11.
//

#ifndef DESIGNPATTERN_OBSERVER_H
#define DESIGNPATTERN_OBSERVER_H

#include <vector>
#include <algorithm>
#include <iostream>
#include "Observable.h"
class Observable;
using namespace std;
class Observer {//观察者
protected:
    double temperature;
    double humidity;
    double pressure;
    Observable* ob;
public:
    Observer(Observable* o);//注册
    virtual void update(double temperature, double humidity, double pressure) = 0;
    virtual void display() = 0;
};



class WeatherNews: public Observer {//天气新闻
public:
    WeatherNews(Observable* o):Observer(o){}
    virtual void update(double temperature, double humidity, double pressure);
    virtual void display();
};



class WeatherForecast: public Observer {//气象预测
public:
    WeatherForecast(Observable* o):Observer(o){}
    virtual void update(double temperature, double humidity, double pressure);
    virtual void display();
    void foreCast();
};


#endif //DESIGNPATTERN_OBSERVER_H
