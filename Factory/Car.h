//
// Created by Administrator on 2016/9/18.
//

#ifndef DESIGN_PATTERN_CAR_H
#define DESIGN_PATTERN_CAR_H

#include <iostream>

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

class OffRoad : public Car {//轿车
public:
    OffRoad():Car(),lossRate(0),fuelLeft(1.0),speed(0){}
    void drive() {
        lossRate += 50;
        fuelLeft -= 0.3;
        speed += 50;
        std::cout << "OffRoad comming VNVNVNVNVNVN" << std::endl;
    }
};
#endif //DESIGN_PATTERN_CAR_H
