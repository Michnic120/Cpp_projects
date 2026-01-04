#pragma once
#include "AirConditioner.h"

class CRoom {
private:
    double dActualTem;
    
public:
    CAirConditioner* cond1;
    short number;
    float plus;   // Temperature increase rate
    float minus;  // Temperature decrease rate
    
    CRoom();
    CRoom(CAirConditioner* condd, float dec, float inc, short num);
    ~CRoom();
    
    void ChangeTem();
    double GiveTem() const;
};
