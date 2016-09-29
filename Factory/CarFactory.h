//
// Created by Administrator on 2016/9/18.
//

#ifndef DESIGN_PATTERN_CARFACTORY_H
#define DESIGN_PATTERN_CARFACTORY_H


class CarFactory {//抽象工厂
public:
    virtual void createWheel();
    virtual void createEngine();
    virtual void createFrame();
};

class AdvancedRoadsterFactory : public CarFactory{//高级跑车工厂
    //...
};

class IntermediateSedanFactory : public CarFactory {//中档轿车工厂
    //..
};
#endif //DESIGN_PATTERN_CARFACTORY_H
