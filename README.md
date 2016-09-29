# 设计模式

**参考资料:HeadFirst设计模式**

##1. Observer
观察者模式类似于用户订阅某个频道,用户就是观察者,频道就是被观察者,被观察者向不同的用户发送消息.<br>
举个例子,天气状况(被观察者)湿度感应装置,温度感应装置,气压感应装置发送数据,如下图:<br>
![天气预报与观察者](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs1.png)
**代码如下**:<br>
```c++
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
```
这些数据可以向不同的布告板发送数据,如下图:<br>
![布告板](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs2.png)<br>
布告板包括了天气新闻,气象预测等,他们继承自Observer覆写了函数<code>update</code>和<code>display</code><br>
```c++
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
```
**各个类的关系图:**
![](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs3.png)<br>
#### 观察者模式UML图总结如下<br>
![观察者模式个各类的关系](https://github.com/RustonOoOo/design-pattern/blob/master/Observer/pic/obs3.png)<br>

---

##2. Decorator
装饰者模式,举个例子,游戏中的武器分为三种有:散弹枪(Scanner),手枪(HandGun),狙击枪(Sniper).然后我们可以用几种附加组件来增强他们的能力,这里我们有激光(Laser),辐射(Radiation),以及电(Electron ),我们怎么才能把任意的组件来粉饰我们的武器呢,用装饰者模式可以很好的做到,参见图<br>
![装饰器模式](https://github.com/RustonOoOo/design-pattern/blob/master/Decorator/pic/dec1.png)

**这是武器的类:**分为三个类狙击枪,手枪,散弹枪<br>
```c++
class Weapon {
public:
    virtual void shoot() = 0;//开枪
    virtual double getDamage() = 0;//计算伤害量
    virtual ~Weapon(){}
};

class ScannerGun : public Weapon {//散弹枪
public:
    virtual void shoot() {
        cout << "Scanner shooting->: ";
    }
    virtual double getDamage() {
        return 1.0;
    }
};
class SniperGun : public Weapon {//狙击枪
public:
    virtual void shoot() {
        cout << "SniperGun shooting->: ";
    }
    virtual double getDamage() {
        return 2.0;
    }
};
class HandGun : public Weapon {//手枪
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
##### 装饰者UML图<br>
![decorator](https://github.com/RustonOoOo/design-pattern/blob/master/Decorator/pic/dec2.jpg)

---

##3. Factory
**工厂模式与抽象工厂模式**:*工厂模式*是在抽象类类中设计一个类似于<code>create()</code>的方法,然后由子类继承之,覆写该方法,以此产生不同的对象.而*抽象工厂*将create方法抽象成一个抽象类,由该类制定如何生产,该方法的好处在于不同的制造厂商可以拥有不同的工厂,将接口与对象解耦.下面是代码中(抽象工厂模式)汽车商家和汽车以及汽车工厂的UML图,代码将在后面给出.<br>
![抽象工厂模式](https://github.com/RustonOoOo/design-pattern/blob/master/Factory/pic/fac1.png)<br>
如图,汽车为所生产的对象,汽车经销商组合了汽车工厂(分为中档轿车工厂,高档跑车工厂),不同的工厂生成汽车的方式不一样,这样就达到解耦效果.下面是代码<br>
**气车类**
```c++
class Car {
protected:
    double lossRate;//损耗度
    double fuelLeft;//剩余油量
    double speed;//速度
public:
    virtual void drive() = 0;
};

class Roadster : public Car {//跑车
public:
    Roadster():Car(),lossRate(0),fuelLeft(1.0),speed(0){}
    void drive() {
        lossRate += 30;
        fuelLeft -= 0.3;
        speed += 100;
        std::cout << "Roadster comming >>>>>" << std::endl;
    }
};

class Sedan : public Car {//轿车
public:
    Sedan():Car(),lossRate(0),fuelLeft(1.0),speed(0){}
    void drive() {
        lossRate += 20;
        fuelLeft -= 0.2;
        speed += 60;
        std::cout << "Sedan comming ~~~~~" << std::endl;
    }
};

class OffRoad : public Car {//越野
public:
    OffRoad():Car(),lossRate(0),fuelLeft(1.0),speed(0){}
    void drive() {
        lossRate += 50;
        fuelLeft -= 0.3;
        speed += 50;
        std::cout << "OffRoad comming VNVNVNVNVNVN" << std::endl;
    }
};
```
<br>
**汽车经销商**<br>
```c++
class CarCompany {
public:
    virtual void repairCar(Car& c) = 0;//修车
    virtual void refuel(Car& c) = 0;//加油
    virtual Car* buildCar() = 0;////用工厂来生产不同的汽车
    void packAll() {//模板方法
        //box();
        //package();
        //buildCar();调用子类方法
    }
};

class Benz : public CarCompany{
    CarFactory* factory;
public:
    Benz(CarFactory* f):CarCompany(),factory(f){}
    virtual void repairCar(Car& c);
    virtual void refuel(Car& c);
    virtual Car* buildCar();//用工厂来生产不同的汽车
};

class Audi : public CarCompany{
    CarFactory* factory;
public:
    Audi(CarFactory* f):CarCompany(),factory(f){}
    virtual void repairCar(Car& c);
    virtual void refuel(Car& c);
    virtual Car* buildCar();
};

class RollsRoyce : public CarCompany{
    CarFactory* factory;
public:
    RollsRoyce(CarFactory* f):CarCompany(),factory(f){}
    virtual void repairCar(Car& c);
    virtual void refuel(Car& c);
    virtual Car* buildCar();
};
```
**抽象工厂类**<br>
```c++
class CarFactory {//抽象工厂
public:
    virtual void createWheel();//生产轮子
    virtual void createEngine();//生产引擎
    virtual void createFrame();//生产汽车框架
};

class AdvancedRoadsterFactory : public CarFactory{//高级跑车工厂
    //...
};

class IntermediateSedanFactory : public CarFactory {//中档轿车工厂
    //..
};
```
##### 抽象工厂UML图<br>
![AbstactFactory](https://github.com/RustonOoOo/design-pattern/blob/master/Factory/pic/fac2.png)<br>
其中,client对应汽车经销商,Factory对应CarFactory,Product对应Car,体现依赖抽象,不依赖具体类的思想
---
