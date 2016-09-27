//
// Created by Administrator on 2016/9/13.
//

#ifndef DESIGN_PATTERN_WEAPONDECORATOR_H
#define DESIGN_PATTERN_WEAPONDECORATOR_H

#include <memory>
#include "Weapon.h"

class WeaponDecorator: public Weapon {

public:
    WeaponDecorator(){}
    void shoot(){};
    double getDamage(){};

};

class Laser : public WeaponDecorator {

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

class Radiation : public WeaponDecorator {
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

class Electron : public WeaponDecorator {
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

#endif //DESIGN_PATTERN_WEAPONDECORATOR_H
