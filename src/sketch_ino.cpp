#include <unistd.h>
#include "core_simulation.h"
#include "SmartMenuLCD.h"
#include "LCDObject.h"

extern LCD myLcd;

//Objects for tests
float setTemp=23.0; 
float currTemp=24.0;
float setLum=200.0;
float setPres=100.0;    //kPa
float currPres=101;     //kPa
string setHeater="ON";
string cool="Cooling:";
string setCool="OFF";
string setLight="ON";


/*
Screen 1 
┌────────────────┐
│Set temp : 23.0 │
│Curr temp: 24.0 │
└────────────────┘
*/
Text           t1s1("Set temp:",0,0);
Text           t2s1("Curr temp:",1,1);
EditableValue  v1s1(&setTemp,11,0,3,-20,80);
Value          v2s1(&currTemp,11,1,3);
Screen         scr1(&t1s1,"Temperature");

/*
Screen 2 
┌────────────────┐
│Heater : ON     │
│Cooling : OFF   │
└────────────────┘
*/

Text           t1s2("Heater:",0,0);
EditableText   t2s2(cool,1,1,8);
EditableText   t3s2(setHeater,11,0,2);
EditableText   t4s2(setCool,11,1,3);
Screen         scr2(&t1s2,"Heating");

/*
Screen 3
┌────────────────┐
│Luminosity: 200 │
│Light : ON      │
└────────────────┘
*/

Text           t1s3("Luminosity:",0,0);
Text           t2s3("Light:",0,1);
EditableValue  v1s3(&setLum,13,0,3,0,900);
EditableText   t3s3(setLight,9,1,2);
Screen         scr3(&t1s3,"Luminosity");

/*
Screen 4
┌────────────────┐
│Set pres: 100   │
│Curr pres: 101  │
└────────────────┘
*/

Text           t1s4("Set pres:",0,0);
Text           t2s4("Curr pres:",1,1);
EditableValue  v1s4(&setPres,11,0,3,0,500);
Value          v2s4(&currPres,12,1,3);
Screen         scr4(&t1s1,"Pressure");

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

    scr2.addObject(&t2s2);
    scr2.addObject(&t3s2);
    scr2.addObject(&t4s2);

    scr3.addObject(&t2s3);
    scr3.addObject(&v1s3);
    scr3.addObject(&t3s3);

    scr4.addObject(&t2s4);
    scr4.addObject(&v1s4);
    scr4.addObject(&v2s4);

    myMenu.addScreen(&scr2);
    myMenu.addScreen(&scr3);
    myMenu.addScreen(&scr4);
        
    myMenu.display();
    myMenu.next();
    myMenu.next();
    myMenu.next();
    myMenu.next();
    myMenu.enter();
}

void Board::loop(){
    /*char buf[100];
    int temp,lum;
    static int bascule=0;
    int i=0;
    for(i=0;i<5;i++){
        temp=analogRead(1);
        lum=analogRead(2);
        pressure=float(analogRead(5))/1000.0;
        sprintf(buf,"temperature %d°C, lum %dlux, pressure %fkPa",temp,lum,pressure);
        //Serial.println(buf);
        sleep(1);
            
        t1.display();
        v.display();
        setTempVal.display();
        t2.display();
        
    
        digitalWrite(3,digitalRead(4)); //btn ctrl smartled
    }
    if(bascule){
        digitalWrite(0,HIGH);
    }else{
        digitalWrite(0,LOW);
    }
    bascule=1-bascule;

    

    while(1);*/
}


