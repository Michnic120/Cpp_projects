#pragma once

class CAirConditioner
{
  private:
      int iMyStatus;
  public:
      CAirConditioner();
      ~AirConditioner();
      void SetAirConditionerON();
      void SetAirConditionerOFF();
      int GiveStatus();
};
