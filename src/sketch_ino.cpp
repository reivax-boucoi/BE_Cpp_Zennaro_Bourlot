#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT); //temp sensor
  pinMode(2, INPUT);    //lum sensor
  pinMode(4, INPUT);    //btn
  pinMode(5, INPUT);    //pressure sensor
  pinMode(0,OUTPUT);    //basic led
  pinMode(3,OUTPUT);    //intelligent led
  
}

// la boucle de controle arduino
void Board::loop(){
    char buf[100];
    int temp,lum,press;
    static int cpt=0;
    static int bascule=0;
    int i=0;
    for(i=0;i<5;i++){
        // lecture sur la pin 1 : capteur de temperature
        temp=analogRead(1);
        lum=analogRead(2);
        press=analogRead(5);
        sprintf(buf,"temperature %ddegC, lum %dlux, pressure %dPa",temp,lum,press);
        Serial.println(buf);
        cpt++;
        sleep(1);
        
        digitalWrite(3,digitalRead(4)); //btn ctrl smartled
    }
    // on eteint et on allume la LED
    if(bascule){
        digitalWrite(0,HIGH);
    }else{
        digitalWrite(0,LOW);
    }
    bascule=1-bascule;

    

    /*myLcd.print("Hello");
    sleep(1);
    myLcd.print(" World !  1");
    sleep(1);
    myLcd.setCursor(0,1);
    myLcd.print(">Coucou !");
    sleep(1);
    myLcd.setCursor(0,1);
    sleep(1);
    myLcd.blink(true);
    while(1);*/
}


