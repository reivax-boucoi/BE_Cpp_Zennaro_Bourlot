#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY*10,TEMP);
  AnalogSensorLuminosity luminosite(DELAY*10,luminosite_environment);
  DigitalActuatorLED led1(DELAY*10);
  IntelligentDigitalActuatorLED led2(DELAY*10,50);
  ExternalDigitalSensorButton btn1(DELAY*10);
  I2CActuatorScreen screen;
  
  
  // branchement des capteurs actionneurs
  esp8266.pin(1,temperature);
  esp8266.pin(2, luminosite);
  esp8266.pin(0,led1);
  esp8266.pin(3,led2);
  esp8266.pin(4,btn1);
  esp8266.i2c(1,screen);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


