
#include "mydevices.h"

using namespace std;

int luminosite_environment = 200; //lux.

//////////////////////////////////////////// SENSORS ////////////////////////////////////////////////////
//classe Sensor
Sensor::Sensor() : Device() {
    sensorMode = PASSIVE;
}

//classe AnalogSensor
AnalogSensor::AnalogSensor(int time, int value) : Sensor(),val(value), temps(time) {
    alea=1;
}

int AnalogSensor::getValue(){
    return val;
}


//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int time,int value):AnalogSensor(time,value){
    name="TemperatureSensor";
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}


//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int time,int value):AnalogSensor(time,value){
 name = "LuminositySensor";
}

void AnalogSensorLuminosity::run() {
	while (1) {
		alea = 1 - alea;
		if (ptrmem != NULL)
			*ptrmem = luminosite_environment + alea;
		sleep(temps);
	}
}

//classe AnalogSensorLuminosity
AnalogSensorPressure::AnalogSensorPressure(int time,int value):AnalogSensor(time,value){
  name = "PressureSensor";
}

void AnalogSensorPressure::run() {
	while (1) {
		alea = 1 - alea;
		if (ptrmem != NULL)
			*ptrmem = val + alea;
		sleep(temps);
	}
}

//class DigitalSensor
DigitalSensor::DigitalSensor(int time) : Sensor(), temps(time) {
    state = OFF;
}

int DigitalSensor::getState(){
    return state;
}

//classe ExternalDigitalSensorButton
ExternalDigitalSensorButton::ExternalDigitalSensorButton(int time):DigitalSensor(time){
 name = "Button";
}


void ExternalDigitalSensorButton::run(){
    while(1){
        if(ifstream("btnON.txt")){
            state=ON;
        }else{
            state=OFF;
        }
        *ptrmem=state;
        sleep(temps);
    }
}


//////////////////////////////////////////// ACTUATORS ////////////////////////////////////////////////////

//classe Actuator
Actuator::Actuator() : Device() {
    actuatorMode = PASSIVE;
}

//classe AnalogActuator
AnalogActuator::AnalogActuator(int time, int value) : Actuator(),val(value), temps(time) {
}

void AnalogActuator::setValue(int data){
    val = data;
}

//classe DigitalActuator
DigitalActuator::DigitalActuator(int time) : Actuator(), temps(time) {
    state = OFF;
}

void DigitalActuator::setState(int newstate){
     state = newstate;
}


//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int time):DigitalActuator(time){
 name = "LED";
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==OFF)
      cout << "(((HEATER OFF)))\n";
    else
    cout << "(((HEATER ON)))\n";
    sleep(temps);
    }
}


//classe IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int time, int inc) : DigitalActuator(time), pState(OFF){
    increment=inc;
    name="SmartLED";
}


void IntelligentDigitalActuatorLED::run(){
  while(1){
        if(ptrmem!=NULL)state=*ptrmem;
        if(state!=pState){
            pState=state;
            if(state)luminosite_environment+=increment;
                else luminosite_environment-=increment;
        }
        if (state==OFF){
            cout << "(((IDA ON)))\n";
        }else{
            cout << "(((IDA OFF)))\n";
        }
        sleep(temps);
    }
}


// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}




