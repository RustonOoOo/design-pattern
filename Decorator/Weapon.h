//
// Created by Administrator on 2016/9/13.
//

#ifndef DESIGN_PATTERN_WEAPON_H
#define DESIGN_PATTERN_WEAPON_H

#include <iostream>
#include <memory>
using namespace std;
class Weapon;
shared_ptr<Weapon> getScnWithLaser();
shared_ptr<Weapon> getHgWithElec();
shared_ptr<Weapon> getSnpWithAll();
void testw();

class Weapon {
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


#endif //DESIGN_PATTERN_WEAPON_H
