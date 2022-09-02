#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(16, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(45, 25, 40) == TOO_HIGH);
  REQUIRE(inferBreach(22, 20, 23) == NORMAL);
}
TEST_CASE("CLASSIFY TEMPERATURE BREACH"){
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 22)==NORMAL); 
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -5)==TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 55)==TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 35)==NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -7)==TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 47)==TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0)==NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -10)==TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 45)==TOO_HIGH);
}
TEST_CASE("checkAndAlert"){
  BatteryCharacter batteryCharacter;
  
  batteryCharacter.coolingType = PASSIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryCharacter,22)==OK); 
  REQUIRE(checkAndAlert(TO_EMAIL,batteryCharacter,35)==OK);
  
  batteryCharacter.coolingType = HI_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryCharacter,55)==OK); 
  REQUIRE(checkAndAlert(TO_EMAIL,batteryCharacter,40)==OK);
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryCharacter,-5)==OK); 
  
  batteryCharacter.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER,batteryCharacter,38)==OK); 
  REQUIRE(checkAndAlert(TO_EMAIL,batteryCharacter,30)==OK);
//  REQUIRE(checkAndAlert(UNKNOWN_TARGET,batteryCharacter,-10)==NOT_OK);
}
TEST_CASE("SendAlert"){
  REQUIRE(SendAlert(NORMAL,TO_CONTROLLER)==OK);
  REQUIRE(SendAlert(TOO_LOW,TO_CONTROLLER)==OK);
  REQUIRE(SendAlert(TOO_HIGH,TO_CONTROLLER)==OK);
  REQUIRE(SendAlert(NORMAL,TO_CONTROLLER)==OK);
  REQUIRE(SendAlert(TOO_LOW,TO_CONTROLLER)==OK);
//  REQUIRE(SendAlert(TOO_HIGH,UNKNOWN_TARGET)==NOT_OK);
}
