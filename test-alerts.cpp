#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOOLOW);
  REQUIRE(inferBreach(16, 20, 30) == TOOLOW);
  REQUIRE(inferBreach(40, 20, 30) == TOOHIGH);
  REQUIRE(inferBreach(45, 25, 40) == TOOHIGH);
  REQUIRE(inferBreach(22, 20, 23) == NORMAL);
}
TEST_CASE("CLASSIFY TEMPERATURE BREACH"){
 REQUIRE(classifyTemperatureBreach(PASSIVECOOLING, 22)==NORMAL); 
  REQUIRE(classifyTemperatureBreach(PASSIVECOOLING, -5)==TOOLOW);
  REQUIRE(classifyTemperatureBreach(PASSIVECOOLING, 55)==TOOHIGH);
  REQUIRE(classifyTemperatureBreach(HIACTIVECOOLING, 35)==NORMAL);
  REQUIRE(classifyTemperatureBreach(HIACTIVECOOLING, -7)==TOOLOW);
  REQUIRE(classifyTemperatureBreach(HIACTIVECOOLING, 47)==TOOHIGH);
  REQUIRE(classifyTemperatureBreach(MEDACTIVECOOLING, 0)==NORMAL);
  REQUIRE(classifyTemperatureBreach(MEDACTIVECOOLING, -10)==TOOLOW);
  REQUIRE(classifyTemperatureBreach(MEDACTIVECOOLING, 45)==TOOHIGH);
}
TEST_CASE("checkAndAlert"){
  BatteryCharacter batteryCharacter;
  
  batteryCharacter.coolingType = PASSIVECOOLING;
  REQUIRE(checkAndAlert(TOCONTROLLER,batteryCharacter,22)==OK); 
  REQUIRE(checkAndAlert(TOEMAIL,batteryCharacter,35)==OK);
  
  batteryCharacter.coolingType = HIACTIVECOOLING;
  REQUIRE(checkAndAlert(TOCONTROLLER,batteryCharacter,55)==OK); 
  REQUIRE(checkAndAlert(TOEMAIL,batteryCharacter,40)==OK);
  REQUIRE(checkAndAlert(TOCONTROLLER,batteryCharacter,-5)==OK); 
  
  batteryCharacter.coolingType = MEDACTIVECOOLING;
  REQUIRE(checkAndAlert(TOCONTROLLER,batteryCharacter,38)==OK); 
  REQUIRE(checkAndAlert(TOEMAIL,batteryCharacter,30)==OK);
//  REQUIRE(checkAndAlert(UNKNOWN_TARGET,batteryCharacter,-10)==NOT_OK);
}
TEST_CASE("SendAlert"){
  REQUIRE(SendAlert(NORMAL,TOCONTROLLER)==OK);
  REQUIRE(SendAlert(TOOLOW,TOCONTROLLER)==OK);
  REQUIRE(SendAlert(TOOHIGH,TOCONTROLLER)==OK);
  REQUIRE(SendAlert(NORMAL,TOCONTROLLER)==OK);
  REQUIRE(SendAlert(TOOLOW,TOCONTROLLER)==OK);
//  REQUIRE(SendAlert(TOO_HIGH,UNKNOWN_TARGET)==NOT_OK);
}
