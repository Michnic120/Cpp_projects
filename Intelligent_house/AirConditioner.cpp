#include "AirConditioner.h"

CAirConditioner::CAirConditioner() : iMyStatus(0) {
    // C++11: Member initializer list
}

CAirConditioner::~CAirConditioner() {
    // Destructor
}

void CAirConditioner::SetAirConditionerON() {
    iMyStatus = 1;
}

void CAirConditioner::SetAirConditionerOFF() {
    iMyStatus = 0;
}

int CAirConditioner::GiveStatus() const {
    return iMyStatus;
}

