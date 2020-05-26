#include <unistd.h>
#include "core_simulation.h"
#include "SmartMenuLCD.h"
#include "LCDObject.h"

extern LCD myLcd;

//Objects for tests
float pressure=0.0;
float setTemp=23.0;
float setLum=200.0;
Value v(&pressure,10,0,4);
                            //(float *ptr, int x, int y, int nbDigits, int min, int max);
EditableValue       setTempVal(  &setTemp,    10,     1,            3,     -10,     100);
Text t1("Pressure :",0,0);
EditableText t2("Text 1 : ",0,1,10);

//Screens for tests

Text           t3("Pressure:",0,0);
EditableText   t4("Temp:",1,0,10);
Text           t5("Lum:",0,0);
Value          v1(&pressure,10,1,4);
EditableValue  v2(&setTemp,10,0,3,-20,80);
Value          v3(&setLum,12,1,4);

Screen scr1(&t3,"Pressure");
Screen scr2(&t4,"Temperature");
Screen scr3(&t5,"Luminosite");
Menu   myMenu(&scr1);


void Board::setup(){
    Serial.begin(9600);
    pinMode(1,INPUT);     //temp sensor
    pinMode(2, INPUT);    //lum sensor
    pinMode(4, INPUT);    //btn
    pinMode(5, INPUT);    //pressure sensor
    pinMode(0,OUTPUT);    //basic led
    pinMode(3,OUTPUT);    //intelligent led
     v2.display();
     sleep(1);
     v2.advanceCursor();
     v2.increment();
     v2.display();
     sleep(1);
     v2.advanceCursor();
     v2.increment();
     v2.display();
     sleep(1);
     v2.advanceCursor();
     v2.decrement();
     v2.display();
     sleep(1);
     v2.advanceCursor();
     v2.decrement();
     v2.display();
     sleep(1);


    //Test Menu...  
    scr1.addObject(&v1);
    scr2.addObject(&v2);
    scr3.addObject(&v3);
    
    scr2.display();
    scr2.Next(); 
    scr2.Prev();  

    ///////Tout ce qui suit fonctionne
/*
    myMenu.addScreen(&scr2);
    myMenu.addScreen(&scr3);
    myMenu.display();  //test ok  
    myMenu.next();
    myMenu.enter();
    myMenu.back();
    myMenu.next();
    myMenu.prev();
*/
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


