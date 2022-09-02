#pragma once

typedef enum {
  PASSIVECOOLING,
  HIACTIVECOOLING,
  MEDACTIVECOOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOOLOW,
  TOOHIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TOCONTROLLER,
  TOEMAIL,
  UNKNOWNTARGET
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

#define OK 0
#define NOT_OK -1
int checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
int SendAlert(BreachType breachType,AlertTarget alerttarget);
