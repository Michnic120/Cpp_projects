#include "Room.h"
#include "AirConditioner.h"

CRoom::CRoom() 
    : dActualTem(18.0), cond1(nullptr), number(0), plus(0.0f), minus(0.0f) {
    // C++11: Member initializer list with default values
}

CRoom::CRoom(CAirConditioner* condd, float dec, float inc, short num)
    : dActualTem(18.0), cond1(condd), plus(inc), minus(dec), number(num) {
    // C++11: Member initializer list
}

CRoom::~CRoom() {
    // Destructor
}

void CRoom::ChangeTem() {
    // Natural temperature increase
    dActualTem += plus;
    
    // Apply air conditioning effect
    int status = cond1->GiveStatus();
    if (status == 1) {
        dActualTem -= minus;
    }
    // If status is 0, temperature only increases naturally
}

double CRoom::GiveTem() const {
    return dActualTem;
}

