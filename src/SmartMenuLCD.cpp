#include "SmartMenuLCD.h"

LCD mylcd;

unsigned int SmartMenuLCD::nbscreens=0;

//methodes de la classe Screen
Screen::Screen(){
   ScreenObject *firstobj = new Text("***MENU***",0,0);
   objects.push_back(firstobj);
    currentObject=0;
}

Screen::Screen(ScreenObject*firstobj){
   objects.push_back(firstobj);
    currentObject=0;
}

void Screen::addObject(ScreenObject*newObj){
    objects.push_back(newObj);
}

ScreenObject* Screen::getPrev(){
    return objects[++currentObject];
}

ScreenObject* Screen::getNext(){
    return objects[--currentObject];
}       

void Screen::display(){
 
     vector<ScreenObject*>::iterator itso;
    for(itso=objects.begin();itso!=objects.end();itso++){
             if(typeid(*itso)==typeid(Value)){
                 ((Value*)(*itso))->display();
              } else {
             ((Text*)(*itso))->display();
            }
    }
}


//methodes de la classe SmartMenuLCD

SmartMenuLCD::SmartMenuLCD(){   
    Screen* newScreen = new Screen();
    screens.push_back(newScreen);
    currentScreen=0;  
    nbscreens++; 
}


SmartMenuLCD::SmartMenuLCD(Screen *s){
    screens.push_back(s);
    currentScreen=0;  
    nbscreens++;  
}

void SmartMenuLCD::addScreen(Screen *s){
    screens.push_back(s);
    nbscreens++; 
}


void SmartMenuLCD::display(){
    unsigned int i = 0;
    
    vector<Screen*>::iterator itsc;

    for (itsc=screens.begin();itsc!=screens.end();itsc++){
        if(i==currentScreen && screenSelected==true){      
                (*itsc)->display();
            }
        i++;
        }
        
}

void SmartMenuLCD::enter(){ //to modify
    mylcd.clear();
 if(currentScreen<nbscreens) {
        currentScreen++;
    }
    screenSelected=true;
    display();
}

void SmartMenuLCD::back(){  //to modify
    mylcd.clear();
    if(currentScreen>0) {
        currentScreen--;
    }
    screenSelected=true;
    display();
}

void SmartMenuLCD::next(){
    mylcd.clear();
 if(currentScreen<nbscreens) {
        currentScreen++;
    }
    screenSelected=true;
    display();
}

void SmartMenuLCD::prev(){
    mylcd.clear();
    if(currentScreen>0) {
        currentScreen--;
    }
    screenSelected=true;
    display();
}





