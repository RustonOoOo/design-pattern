//
// Created by Administrator on 2016/9/11.
//

#include "Observer.h"

void Observable::addObserver(Observer *observer) {
    obs.push_back(observer);
}
void Observable::notifyDataChanged() {
    for(Observer* observer : obs) {
        observer->update(temperature,humidity,pressure);
    }
}