#include <unistd.h>
#include "core_simulation.h"
#include "SmartMenuLCD.h"
#include "LCDObject.h"

float pressure=0.0;

void Board::setup(){
    Serial.begin(9600);
    pinMode(1,INPUT); //temp sensor
    pinMode(2, INPUT);    //lum sensor
    pinMode(4, INPUT);    //btn
    pinMode(5, INPUT);    //pressure sensor
    pinMode(0,OUTPUT);    //basic led
    pinMode(3,OUTPUT);    //intelligent led

    //Value press_value(&pressure,0,0,2);
    myLcd.print("Hello");
    sleep(1);
    myLcd.print(" World !  1");
    sleep(1);
    myLcd.setCursor(0,1);
    myLcd.print(">");
    myLcd.print(5.41,1);
    sleep(1);
    myLcd.setCursor(0,1);
    sleep(1);
    myLcd.blink(true);
}

void Board::loop(){
    char buf[100];
    int temp,lum;
    static int bascule=0;
    int i=0;
    for(i=0;i<5;i++){
        temp=analogRead(1);
        lum=analogRead(2);
        pressure=float(analogRead(5))/1000.0;
        sprintf(buf,"temperature %ddegC, lum %dlux, pressure %fkPa",temp,lum,pressure);
        //Serial.println(buf);
        
        sleep(1);
        
        digitalWrite(3,digitalRead(4)); //btn ctrl smartled
    }
    if(bascule){
        digitalWrite(0,HIGH);
    }else{
        digitalWrite(0,LOW);
    }
    bascule=1-bascule;

    

    while(1);
}


