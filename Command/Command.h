//
// Created by Administrator on 2016/9/22.
//

#ifndef DESIGN_PATTERN_COMMAND_H
#define DESIGN_PATTERN_COMMAND_H

#include <vector>
#include <memory>
#include <iostream>
#include "Staff.h"
using namespace std;
class Command{//interface
public:
    virtual void excute()=0;//执行命令
    virtual void undo() = 0;//回滚
};

class LightOn : public Command {//开灯
private:
    std::shared_ptr<Light> light;
public:
    LightOn(Light* l):
            light(l){}

public:
    void excute()override{light->turnon();}
    void undo()override {light->undo();}
};

class LightOff : public Command {//关灯
private:
    Light* light;
public:
    LightOff(Light* l):
    light(l){}
public:
    void excute()override{light->turnoff();}
    void undo()override {light->undo();}
};

class FanRotateSlow: public Command {//风扇低速转动
private:
    ElectricFan* efan;
public:
    FanRotateSlow(ElectricFan* e):efan(e){}
    void excute()override{efan->low();}
    void undo()override {efan->undo();}
};
class FanOff: public Command {//风扇低速转动
private:
    ElectricFan* efan;
public:
    FanOff(ElectricFan* e):efan(e){}
    void excute()override{efan->off();}
    void undo()override {efan->undo();}
};

class FanRotateMedium : public Command {//中速转动
private:
    ElectricFan* efan;
public:
    FanRotateMedium(ElectricFan* e):efan(e){}
    void excute()override{efan->mid();}
    void undo()override {efan->undo();}
};
class FanRotateFast : public Command {//高速转动
private:
    ElectricFan* efan;
public:
    FanRotateFast(ElectricFan* e):efan(e){}
    void excute()override{efan->high();}
    void undo()override {efan->undo();}
};

struct NULLCMD : public Command{//空命令
public:
    virtual void excute(){}//
    virtual void undo(){}
};

class TurnOnAll: public Command {//开启所有执行命令
private:
    vector<Command*> commands;
public:
    TurnOnAll(vector<Command*> cmds):commands(cmds){}

    void excute()override{
        for(auto p : commands) {
            p->excute();
        }
    }
    void undo()override {
        cerr << "cannot undo" << endl;
    }
};
#endif //DESIGN_PATTERN_COMMAND_H
