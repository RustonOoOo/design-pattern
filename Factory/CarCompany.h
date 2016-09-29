//
// Created by Administrator on 2016/9/18.
//

#ifndef DESIGN_PATTERN_CARCOMPANY_H
#define DESIGN_PATTERN_CARCOMPANY_H

#include "Car.h"
#include "CarFactory.h"

class CarCompany {
public:
    virtual void repairCar(Car& c) = 0;
    virtual void refuel(Car& c) = 0;
    virtual Car* buildCar() = 0;
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
    virtual Car* buildCar();
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
#endif //DESIGN_PATTERN_CARCOMPANY_H
