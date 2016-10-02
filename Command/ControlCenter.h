//
// Created by Administrator on 2016/9/22.
//

#ifndef DESIGN_PATTERN_CONTROLCENTER_H
#define DESIGN_PATTERN_CONTROLCENTER_H

#include "Command.h"
#include <map>
#include <bits/shared_ptr.h>

using namespace std;

class ControlCenter {//遥控器
private:
    typedef int ButtonNum;
    map<ButtonNum, Command *> on;
    map<ButtonNum, Command *> off;
    Command* lastexec;//上一个命令
public:
    ControlCenter():lastexec(new NULLCMD){}
    void addCommand(ButtonNum num, Command *cmdOn,Command* cmdOff) {
        on[num] = cmdOn;
        off[num] = cmdOff;
    }

    void removeCommand(ButtonNum num) {
        on.erase(num);
        off.erase(num);
    }

    void buttonOn(ButtonNum num) {
        lastexec = on[num];
        on[num]->excute();
    }
    void buttonOff(ButtonNum num) {
        lastexec = off[num];
        off[num]->excute();
    }
    void undo(ButtonNum num) {//回滚上一个状态
        lastexec->undo();
    }
};

#endif //DESIGN_PATTERN_CONTROLCENTER_H
