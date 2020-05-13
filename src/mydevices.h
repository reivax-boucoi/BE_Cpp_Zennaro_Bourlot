#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "core_simulation.h"

extern int luminosite_environment;

//////////////////////////////////////////// SENSORS ////////////////////////////////////////////////////
//classe generique pour tout type de capteur
class Sensor : public Device {
 protected:
    int sensorMode;
 public:
    virtual const char* getSensorName() = 0;

    Sensor();
};

//definition de la classe generique pour tous les capteurs analogiques
class AnalogSensor : public Sensor {
 protected:
  // fait osciller la valeur du capteur de 1
  int alea;
  // valeur du capteur mesure
  int val;
  // temps entre 2 prises de valeurs
  int temps;  
    
public:
    
    AnalogSensor(int time, int value);
    
    int getValue();
};

//definition de la classe generique pour tous les capteurs ON/OFF
class DigitalSensor : public Sensor {
 protected:
    //etat ON ou OFF du capteur
    int state;
    // temps avant un changement d'etat
    int temps;  
 public:
    
    DigitalSensor(int time);

    int getState();
};

// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public AnalogSensor {
private:
 
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int time, int value);
    //Type du capteur
   virtual const char* getSensorName();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

// Classe du capteur de luminosité
class AnalogSensorLuminosity : public AnalogSensor {
private:

public:
	//constructeur
	AnalogSensorLuminosity(int time, int value);
    //Type du capteur
    virtual const char* getSensorName();
	// thread representant le capteur et permettant de fonctionner independamment de la board
	virtual void run();
};

// Classe du capteur de pression
class AnalogSensorPressure : public AnalogSensor {
private:

public:
	//constructeur
	AnalogSensorPressure(int time, int value);
    //Type du capteur
    virtual const char* getSensorName();
	// thread representant le capteur et permettant de fonctionner independamment de la board
	virtual void run();
};

class ExternalDigitalSensorButton : public DigitalSensor{
private :
    
public :
    ExternalDigitalSensorButton(int time);
    //Type du capteur
    virtual const char* getSensorName();
    // thread representant le bouton et permettant de fonctionner independamment de la board
    virtual void run();
};

//////////////////////////////////////////// ACTUATORS ////////////////////////////////////////////////////

//classe generique pour tout type de capteur
class Actuator : public Device {
 protected:
    int actuatorMode;
 public:
    //Type d'actionneur
    virtual const char* getActuatorName() = 0;

    Actuator();
};

//definition de la classe generique pour tous les actionneurs analogiques
class AnalogActuator : public Actuator {
 protected:
  
  int val;
  // temps entre 2 prises de valeurs
  int temps;  
    
public:
    
    AnalogActuator(int time, int value);
    
    void setValue(int data);
};

//definition de la classe generique pour tous les actionneurs ON/OFF
class DigitalActuator : public Actuator {
 protected:
    //etat ON ou OFF de l'actionneur
    int state;
    // temps avant un changement d'etat
    int temps;  
 public:
    
    DigitalActuator(int time);

    void setState(int newstate);
};

// exemple d'actionneur digital : une led.
class DigitalActuatorLED: public DigitalActuator {
private:

public:
    // initialisation du temps de rafraichissement
  DigitalActuatorLED(int time);
 //Type d'actionneur
    virtual const char* getActuatorName();
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};



class IntelligentDigitalActuatorLED : public DigitalActuator{
    private:
        //increment de luminosite
        int increment; 
        //etat precedent
        int pState;
public:
    // initialisation du temps de rafraichissement
    IntelligentDigitalActuatorLED(int time, int inc);
    //Type d'actionneur
    virtual const char* getActuatorName();
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};


// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

#endif
