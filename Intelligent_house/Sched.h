#pragma once
#include <array>
#include <string>
#include "Room.h"
#include "Controller.h"

class CSched {
private:
    int iTimeCycle;
    CRoom* room1;
    CRoom* room2;
    CRoom* room3;
    CRoom* room4;
    CRoom* room5;
    CController* con1;
    CController* con2;
    CController* con3;
    CController* con4;
    CController* con5;
    
    void clearScreen();
    
public:
    CSched(CRoom* rom1, CController* cont1, CRoom* rom2, CController* cont2,
           CRoom* rom3, CController* cont3, CRoom* rom4, CController* cont4,
           CRoom* rom5, CController* cont5, int cycle);
    ~CSched();
    
    void Starter();
};
