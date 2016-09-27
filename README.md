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

---

##2. Decorator
装饰者模式,举个例子,游戏中的武器分为三种有:散弹枪(Scanner),手枪(HandGun),狙击枪(Sniper).然后我们可以用几种附加组件来增强他们的能力,这里我们有激光(Laser),辐射(Radiation),以及电(Electron ),我们怎么才能把任意的组件来粉饰我们的武器呢,用装饰者模式可以很好的做到,参见图<br>
![装饰器模式](https://github.com/RustonOoOo/design-pattern/blob/master/Decorator/pic/dec1.png)

**这是武器的类:**<br>
```c++
lass Weapon {
public:
    virtual void shoot() = 0;//开枪
    virtual double getDamage() = 0;//计算伤害量
    virtual ~Weapon(){}
};

class ScannerGun : public Weapon {
public:
    virtual void shoot() {
        cout << "Scanner shooting->: ";
    }
    virtual double getDamage() {
        return 1.0;
    }
};
class SniperGun : public Weapon {
public:
    virtual void shoot() {
        cout << "SniperGun shooting->: ";
    }
    virtual double getDamage() {
        return 2.0;
    }
};
class HandGun : public Weapon {
public:
    virtual void shoot() {
        cout << "HandGun shooting->: ";
    }
    virtual double getDamage() {
        return 0.5;
    }
};
```
**这是组件的类**:他们继承了武器,然后又组合了武器,这样的好处在于,我们可以将用<code>Weapon* w = Laser(Gun)</code>生成一个镭射枪后,为了再给他加上任意余下的组件我们可以:<code>w = Radiation(w)</code>也可以<code>w = Electron(w)</code>甚至可以加双倍的镭射等等,这样将武器与组件联系在一起又不至于太耦合,依赖抽象而不是依赖具体类!(**可以改进的地方**:用智能指针)
```c++
class WeaponDecorator: public Weapon {//包裹器抽象类

public:
    WeaponDecorator(){}
    void shoot(){};
    double getDamage(){};

};

class Laser : public WeaponDecorator {//激光

protected:
    const static double LaserDamage;
    Weapon* wrapped;
public:
    Laser(Weapon* wp):wrapped(wp){}
    virtual void shoot() {
        wrapped->shoot();
        cout << "===-L-A-S-E-R--===";
    }
    virtual double getDamage() {
        return wrapped->getDamage() + LaserDamage;
    }
};
const double Laser::LaserDamage = 5.0;

class Radiation : public WeaponDecorator {//辐射
protected:
    Weapon* wrapped;
    const static double RadiationDamage;
public:
    Radiation(Weapon* wp):wrapped(wp){}
    virtual void shoot() {
        wrapped->shoot();
        cout << "^^^^@@@Rad!$%^&*(_" << endl;
    }
    virtual double getDamage() {
        return wrapped->getDamage() + RadiationDamage;
    }
};
const double Radiation::RadiationDamage = 2.0;

class Electron : public WeaponDecorator {//电
protected:
    Weapon* wrapped;
    const static double ElectronDamage;
public:
    Electron(Weapon* wp):wrapped(wp){}
    virtual void shoot() {
        wrapped->shoot();
        cout << "~~~~^^ELE>>>--~~";
    }
    virtual double getDamage() {
        return wrapped->getDamage() + ElectronDamage;
    }
};
const double Electron::ElectronDamage = 4.0;
```

**测试:**
```c++
void testw() {
    cout << "Laser-Scanner:" << endl;
    auto gun1 = new Laser(new Sniper);
    gun1->shoot();
    cout << "with damage :" << gun1->getDamage();
    cout << endl;
    cout << "All-SniperGun:" << endl;
    auto gun2 = new Radiation(new Electron((new Laser(new Sniper))));
    gun2->shoot();
    cout << "with damage :" << gun2->getDamage();
    cout << endl;
    cout << "Elec-HandGun:"<<endl;
    auto gun3 = new Electron(new HandGun);
    gun3->shoot();
    cout << "with damage :" << gun3->getDamage();
    cout << endl;
}
```
**输出:***
```
Laser-Scanner:
Scanner shooting->: ===-L-A-S-E-R--===with damage :6
A

All-SniperGun:
SniperGun shooting->: ~~~~^^ELE>>>--~~===-L-A-S-E-R--===^^^^@@@Rad!$%^&*(_
with damage :13
Elec-HandGun:
HandGun shooting->: ~~~~^^ELE>>>--~~with damage :4.5
```
**总结UML图**
![decorator](https://github.com/RustonOoOo/design-pattern/blob/master/Decorator/pic/dec2.jpg)
