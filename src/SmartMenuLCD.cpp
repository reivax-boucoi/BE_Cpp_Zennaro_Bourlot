#include "SmartMenuLCD.h"

LCD mylcd;

unsigned int Menu::nbscreens=0;

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


//methodes de la classe Menu

Menu::Menu(){   
    Screen* newScreen = new Screen();
    screens.push_back(newScreen);
    currentScreen=0;  
    nbscreens++; 
}


Menu::Menu(Screen *s){
    screens.push_back(s);
    currentScreen=0;  
    nbscreens++;  
}

void Menu::addScreen(Screen *s){
    screens.push_back(s);
    nbscreens++; 
}


void Menu::display(){
    unsigned int i = 0;
    
    vector<Screen*>::iterator itsc;

    for (itsc=screens.begin();itsc!=screens.end();itsc++){
        if(i==currentScreen && screenSelected==true){      
                (*itsc)->display();
            }
        i++;
        }
        
}

void Menu::enter(){ //to modify
    mylcd.clear();
 if(currentScreen<nbscreens) {
        currentScreen++;
    }
    screenSelected=true;
    display();
}

void Menu::back(){  //to modify
    mylcd.clear();
    if(currentScreen>0) {
        currentScreen--;
    }
    screenSelected=true;
    display();
}

void Menu::next(){
    mylcd.clear();
 if(currentScreen<nbscreens) {
        currentScreen++;
    }
    screenSelected=true;
    display();
}

void Menu::prev(){
    mylcd.clear();
    if(currentScreen>0) {
        currentScreen--;
    }
    screenSelected=true;
    display();
}





