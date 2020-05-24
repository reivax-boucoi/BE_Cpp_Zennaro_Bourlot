#include <unistd.h>
#include "core_simulation.h"
#include "SmartMenuLCD.h"
#include "LCDObject.h"

extern LCD myLcd;

//Objects for tests
float pressure=0.0;
float setTemp=23.0;
Value v(&pressure,10,0,4);
EditableValue setTempVal(&setTemp,10,1,3,-10,100);
Text t1("Pressure :",0,0);
EditableText t2("Text 1 : ",0,1,10);

//Screens for tests

Text *t3 = new Text("Pressure:",0,0);
Value *v1 = new Value(&pressure,10,1,4);
Text *t4 = new Text("Temperature:",0,0);
Value *v2 = new Value(&setTemp,12,1,2);

Screen *scr1 = new Screen(t3,"Pressure");
Screen *scr2 = new Screen(t4,"Temperature");

Menu *myMenu = new Menu(scr1);


void Board::setup(){
    Serial.begin(9600);
    pinMode(1,INPUT); //temp sensor
    pinMode(2, INPUT);    //lum sensor
    pinMode(4, INPUT);    //btn
    pinMode(5, INPUT);    //pressure sensor
    pinMode(0,OUTPUT);    //basic led
    pinMode(3,OUTPUT);    //intelligent led
    
   /* t1.display();
    v.display();
    setTempVal.display();
    
    t2.addText("Text 2 : ");
    t2.addText("Text 3 : ");
    t2.display();
    t2.next();    //next and prev testing OK
    t2.display();
    t2.next();
    t2.display();
    t2.next();
    t2.display();
    t2.prev();
    t2.display();
    t2.prev();
    t2.display();*/

    //Test Menu...
    scr1->addObject(v1);
    //scr1->display();  //test ok
    scr2->addObject(v2);
    //scr2->display();    //test ok
    myMenu->addScreen(scr2);
    myMenu->display();  //test ok  
    myMenu->next();
    myMenu->enter();
    myMenu->back();
    myMenu->next();
    myMenu->prev();

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
        sprintf(buf,"temperature %d°C, lum %dlux, pressure %fkPa",temp,lum,pressure);
        //Serial.println(buf);
        sleep(1);
            
        /*t1.display();
        v.display();
        setTempVal.display();
        t2.display();*/
        
    
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


