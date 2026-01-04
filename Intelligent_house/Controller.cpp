#include "Controller.h"
#include "AirConditioner.h"
#include "Room.h"

CController::CController(CAirConditioner* condd, CRoom* room, int temtem)
    : dTempSet(static_cast<double>(temtem)), cond(condd), room1(room) {
    // C++11: Member initializer list
}

CController::~CController() {
    // Destructor
}

void CController::SetTemp(float temp) {
    dTempSet = static_cast<double>(temp);
}

void CController::IncreaseTemp() {
    dTempSet += 1.0;
}

void CController::DecreaseTemp() {
    dTempSet -= 1.0;
}

double CController::GiveTemp() const {
    return dTempSet;
}

void CController::Control() {
    double currentTemp = room1->GiveTem();
    
    // Hysteresis control with 0.5°C deadband
    if (currentTemp < dTempSet - 0.5) {
        cond->SetAirConditionerOFF();  // Too cold, turn off cooling
    } 
    else if (currentTemp > dTempSet + 0.5) {
        cond->SetAirConditionerON();   // Too hot, turn on cooling
    }
    // Otherwise, maintain current state
}

