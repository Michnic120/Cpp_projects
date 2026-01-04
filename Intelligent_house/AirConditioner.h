#pragma once

class CAirConditioner {
private:
    int iMyStatus;
    
public:
    CAirConditioner();
    ~CAirConditioner();
    
    void SetAirConditionerON();
    void SetAirConditionerOFF();
    int GiveStatus() const;
    
    // C++11: Delete copy operations (if using unique ownership)
    // CAirConditioner(const CAirConditioner&) = delete;
    // CAirConditioner& operator=(const CAirConditioner&) = delete;
};
