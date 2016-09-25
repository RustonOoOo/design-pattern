# 设计模式

**参考资料:HeadFirst设计模式**

##1. Observer
观察者模式类似于用户订阅某个频道,用户就是观察者,频道就是被观察者,被观察者向不同的用户发送消息.<br>
举个例子,天气状况(被观察者)湿度感应装置,温度感应装置,气压感应装置发送数据,如下图:<br>
![天气预报与观察者](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs1.png)
**代码如下**:<br>
```c++
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
    void addObserver(Observer* observer);//添加观察者
    void deleteObserver(Observer* observer){//删除某个观察者
        auto positon = std::find(obs.begin(), obs.end(), observer);
        obs.erase(positon);
    }
    void notifyDataChanged();//通知所有观察者
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
```
这些数据可以向不同的布告板发送数据,如下图:<br>
![布告板](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs2.png)<br>
布告板包括了天气新闻,气象预测等,他们继承自Observer覆写了函数<code>update</code>和<code>display</code><br>
```c++
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
    Observer(Observable* o);//注册自己
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
```
**各个类的关系图:**
![](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs3.png)<br>
#### 观察者模式UML图总结如下<br>
![观察者模式个各类的关系](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs3.png)<br>
