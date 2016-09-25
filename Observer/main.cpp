#include <iostream>
#include "Observer.h"

int test() {
    WeatherData wd;
    WeatherNews wn(&wd);
    WeatherForecast wf(&wd);
    wd.setData(1,2,3);
    wd.notifyDataChanged();
    wn.display();
    wf.display();
    wd.setData(5,6,7);
    wd.notifyDataChanged();
    wn.display();
    wf.display();
}