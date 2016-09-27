//
// Created by Administrator on 2016/9/13.
//

#include "Weapon.h"

#include "WeaponDecorator.h"
void testw() {
    cout << "Laser-Scanner:" << endl;
    auto gun1 = getScnWithLaser();
    gun1->shoot();
    cout << "with damage :" << gun1->getDamage();
    cout << endl;
    cout << "All-SniperGun:" << endl;
    auto gun2 = getSnpWithAll();
    gun2->shoot();
    cout << "with damage :" << gun2->getDamage();
    cout << endl;
    cout << "Elec-HandGun:"<<endl;
    auto gun3 = getHgWithElec();
    gun3->shoot();
    cout << "with damage :" << gun3->getDamage();
    cout << endl;
}
shared_ptr<Weapon> getScnWithLaser() {
    Weapon* sg = new ScannerGun;
    //Weapon* laser = new Laser(sg);
    return make_shared<Laser>(sg);//不能用make_shared<Laser>(new Laser(sg))
}

shared_ptr<Weapon> getHgWithElec() {
    Weapon* hg = new HandGun;
    //Weapon* elec = new Electron(hg);
    return make_shared<Electron>(hg);
}

shared_ptr<Weapon> getSnpWithAll() {
    Weapon* snp = new SniperGun;
    Weapon* elec = new Electron(snp);
    Weapon* laser = new Laser(elec);
    Radiation* rad = new Radiation(laser);
    return shared_ptr<Radiation>(rad);
}