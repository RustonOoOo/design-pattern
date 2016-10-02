//
// Created by Administrator on 2016/9/22.
//

#ifndef DESIGN_PATTERN_STAFF_H
#define DESIGN_PATTERN_STAFF_H

struct Light{
    bool lastState;
    bool isLightOn;
    Light():lastState(false),isLightOn(false){}
    void turnon() {
        lastState = isLightOn;
        isLightOn = true;
    }
    void turnoff() {
        lastState = isLightOn;
        isLightOn = false;
    }
    void undo() {
        isLightOn = lastState;
    }
};

struct ElectricFan{
    int lastState;
    int speed;
    ElectricFan():speed(0),lastState(0){}
    void off(){lastState = speed;speed = 0;}
    void low(){lastState = speed;speed = 5;}
    void mid(){lastState = speed;speed = 7;}
    void high(){lastState = speed;speed = 10;}
    void undo(){speed = lastState;}
};

#endif //DESIGN_PATTERN_STAFF_H
