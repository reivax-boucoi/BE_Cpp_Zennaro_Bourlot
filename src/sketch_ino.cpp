#include <unistd.h>
#include "core_simulation.h"
#include "SmartMenuLCD.h"
#include "LCDObject.h"
#include "Encoder.h"


extern LCD myLcd;

//Objects for tests
float pressure=0.0;
float setTemp=23.0;
float currTemp=24.0;
float lum=200.0;

/*
Screen 1 
┌────────────────┐
│Set temp : 23.0 │
│Curr temp: 24.0 │
└────────────────┘
*/
Text           t1s1("Set temp :",0,0);
Text           t2s1("Curr temp:",1,0);
EditableValue  v1s1(&setTemp,11,0,3,-20,80);
Value          v2s1(&currTemp,11,0,3);
Screen         scr1(&t1s1,"Temperature");




Value          v1(&pressure,10,1,4);
Value          v3(&lum,12,1,4);

Screen scr2(&v1,"Temperature");
Screen scr3(&v3,"Luminosite");
Menu   myMenu(&scr1);


void Board::setup(){
    Serial.begin(9600);
    pinMode(1,INPUT);     //temp sensor
    pinMode(2, INPUT);    //lum sensor
    pinMode(4, INPUT);    //btn
    pinMode(5, INPUT);    //pressure sensor
    pinMode(0,OUTPUT);    //basic led
    pinMode(3,OUTPUT);    //intelligent led

    //Filling menus
    scr1.addObject(&t2s1);
    scr1.addObject(&v1s1);
    scr1.addObject(&v2s1);
    
    
    myMenu.addScreen(&scr1);
    myMenu.addScreen(&scr2);
    myMenu.display();
}

void Board::loop(){
    
    currTemp=analogRead(1);
    lum=analogRead(2);
    pressure=float(analogRead(5))/1000.0;
    
    digitalWrite(3,digitalRead(4)); //btn ctrl smartled
    char enc = getEncoderValue();
    switch(enc){
        case '+':
            myMenu.next();
            break;
        case '-':
            myMenu.prev();
            break;
        case 'e':
            myMenu.enter();
            break;
        case 'b':
            myMenu.back();
            break;
            
        default :
            //do nothing
            break;
    }
  

    

}


