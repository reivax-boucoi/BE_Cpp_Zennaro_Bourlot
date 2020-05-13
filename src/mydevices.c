
#include "mydevices.h"

using namespace std;

int luminosite_environment = 200; //lux.

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
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
AnalogSensorLuminosity::AnalogSensorLuminosity(int tps, int data) : Device(), val(data), temps(tps) {
	alea = 1;
}


void AnalogSensorLuminosity::run() {
	while (1) {
		alea = 1 - alea;
		if (ptrmem != NULL)
			*ptrmem = luminosite_environment + alea;
		sleep(temps);
	}
}



//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}


//classe IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t, int inc) : Device(), state(LOW), temps(t), pState(LOW){
    increment=inc;
}

void IntelligentDigitalActuatorLED::run(){
  while(1){
        if(ptrmem!=NULL)state=*ptrmem;
        if(state!=pState){
            pState=state;
            if(state)luminosite_environment+=increment;
                else luminosite_environment-=increment;
        }
        if (state==LOW){
            cout << "((((IDALeteint"<<luminosite_environment<<"))))\n";
        }else{
            cout << "((((IDALallume"<<luminosite_environment<<"))))\n";
        }
        sleep(temps);
    }
}

//class ExternalDigitalSensorButton

ExternalDigitalSensorButton::ExternalDigitalSensorButton(int t) : Device(), state(LOW){
    
}

void ExternalDigitalSensorButton::run(){
    while(1){
        if(ifstream("btnON.txt")){
            state=HIGH;
        }else{
            state=LOW;
        }
        *ptrmem=state;
        sleep(1);
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

