#include "SmartMenuLCD.h"

//methodes de la classe Screen
Screen::Screen(){
    Text firstobj("*** MENU ***");
    objects.push_back(firstobj);
}
    

//methodes de la classe SmartMenuLCD
SmartMenuLCD::SmartMenuLCD(){
    
    Screen newScreen();

    screens.push_back(newScreen);
    currentScreen=0;   
}

SmartMenuLCD::SmartMenuLCD(Screen *s){

    screens.push_back(*s);
    currentScreen=0;   
}

void SmartMenuLCD::AddScreen(Screen *s){
    screens.push_back(*s);
}

void SmartMenuLCD::display(){
    int i,j;
    <ScreenObject>::iterator itso;

    for (i=0;i<screens.size();i++){
        if(i==currentScreen){
            for(itso=screens[i].begin();itso=screens[i].end();itso++){
                if(typeid(*itso)==typeid(Value)){
                    mylcd.print(3.14,2);
                } else {                    //donnees brutes pour tester...
                    mylcd.print("MENU");
                }
            }
        }
    }
}

void SmartMenuLCD::enter(){
    currentScreen++;
    screenSelected=true;
    display();
}

void SmartMenuLCD::back(){
    currentScreen--;
    display();
}







