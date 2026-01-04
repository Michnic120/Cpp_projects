#pragma once
#include "AirConditioner.h"
#include "Room.h"

class CController {
private:
    double dTempSet;
    CAirConditioner* cond;
    CRoom* room1;
    
public:
    CController(CAirConditioner* condd, CRoom* room, int temtem);
    ~CController();
    
    void SetTemp(float temp);
    void IncreaseTemp();
    void DecreaseTemp();
    double GiveTemp() const;
    void Control();
};
