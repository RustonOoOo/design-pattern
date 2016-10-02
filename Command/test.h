//
// Created by Administrator on 2016/9/25.
//

#ifndef DESIGN_PATTERN_TEST_H
#define DESIGN_PATTERN_TEST_H

#include "Staff.h"
#include "ControlCenter.h"
#include "Command.h"
void testcmd() {
    Light l;
    LightOn lightOn(&l);
    LightOff lightOff(&l);
    ControlCenter ctrl;
    ctrl.addCommand(0,&lightOn,&lightOff);
    ctrl.buttonOn(0);
    ctrl.buttonOff(0);
    ctrl.undo(0);
    string info = l.isLightOn?"light on":"light off";
    cout << info << endl;

    ElectricFan ef;
    FanRotateSlow fs(&ef);
    FanRotateFast ff(&ef);
    FanRotateMedium fm(&ef);
    FanOff fo(&ef);

    ctrl.addCommand(1,&fs, &fo);
    ctrl.addCommand(2,&ff, &fo);
    ctrl.addCommand(3,&fm, &fo);

    ctrl.buttonOn(1);
    ctrl.buttonOn(2);
    ctrl.buttonOn(3);
    ctrl.undo(2);
    cout << "speed: " <<ef.speed<<endl;

    vector<Command*> cmds;
    TurnOnAll toa(cmds);
    toa.excute();
}
#endif //DESIGN_PATTERN_TEST_H
