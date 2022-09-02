#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOOLOW;
  }
  else if(value > upperLimit) 
  {
    return TOOHIGH;
  }
  else
  {
  return NORMAL;}
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  if(coolingType == PASSIVECOOLING)
  {
    lowerLimit = 0;
      upperLimit = 35;
  }
  else if(coolingType == HIACTIVECOOLING)
  {
    lowerLimit = 0;
      upperLimit = 45;
  }
  else
  {
   lowerLimit = 0;
      upperLimit = 40; 
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
return SendAlert(breachType,alertTarget);
}
int SendAlert(BreachType breachtype,AlertTarget alerttarget)
{
  if(alerttarget == TOCONTROLLER)
  {
   sendToController(breachtype);
    return OK;
  }
  if(alerttarget == TOEMAIL)
  {
   sendToEmail(breachtype);
    return OK;
  }
  printf("Unknown Alert TArget\n");
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType == TOOLOW)
  {
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
  }
  else if(breachType == TOOHIGH)
  {
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
  }
  else
  {
   // do nothing 
  }
}
