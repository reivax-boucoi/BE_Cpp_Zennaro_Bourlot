#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(DELAY*20,TEMP);
  AnalogSensorLuminosity luminosite(DELAY*20,luminosite_environment);
  DigitalActuatorLED led1(DELAY*4);
  IntelligentDigitalActuatorLED led2(DELAY*20,50);
  ExternalDigitalSensorButton btn1(DELAY*20);
  AnalogSensorPressure pressure(DELAY*20,101325);
  I2CActuatorScreen screen;
  
  
  // branchement des capteurs actionneurs
  esp8266.pin(1,temperature);
  esp8266.pin(2, luminosite);
  esp8266.pin(0,led1);
  esp8266.pin(3,led2);
  esp8266.pin(4,btn1);
  esp8266.pin(5, pressure);
  esp8266.i2c(1,screen);
  
  // allumage de la carte
  esp8266.run();
  return 0;
}


