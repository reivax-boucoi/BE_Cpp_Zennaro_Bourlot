#include "SmartMenuLCD.h"

LCD mylcd;

unsigned int Menu::nbscreens=0;
unsigned int Screen::nbobjects=0;

//methodes de la classe Screen

Screen::Screen(ScreenObject*firstobj,string nom){
   objects.push_back(firstobj);
    currentObject=0;
    nbobjects++;
    name=nom;
}

void Screen::addObject(ScreenObject*newObj){
    objects.push_back(newObj);
    nbobjects++;
}

string Screen::getName(){
    return name;
}

void Screen::Next(){
    unsigned int i;
    if(currentObject==nbobjects-1) currentObject--;
    for(i=currentObject+1;i<nbobjects;i++){
        if(typeid(*objects[i])==typeid(EditableValue) || typeid(*objects[i])==typeid(EditableText)){
            currentObject=i;
            mylcd.clear();
            mylcd.setCursor(objects[i]->getx()-1,objects[i]->gety());
            mylcd.print(">");
            this->display();
            break;
        }
    }
}

void Screen::Prev(){
    int i;
    if(currentObject==0) currentObject++;
    for(i=currentObject-1;i>=0;i--){
        if(typeid(*objects[i])==typeid(EditableValue) || typeid(*objects[i])==typeid(EditableText)){
            currentObject=i;
            mylcd.clear();
            mylcd.setCursor(objects[i]->getx()-1,objects[i]->gety());
            mylcd.print(">");
            this->display();
            break;
        }
    }
}



void Screen::display(){
 
     vector<ScreenObject*>::iterator itso;
    for(itso=objects.begin();itso!=objects.end();itso++){
             if(typeid(*itso)==typeid(Value)){
                 ((Value*)(*itso))->display();
              } 
                /*else if(typeid(*itso)==typeid(EditableValue){
                    ((EditableValue*)(*itso))->display();
                }
                else if(typeid(*itso)==typeid(EditableText){
                    ((EditableText*)(*itso))->display();
                }*/
             else {
             ((Text*)(*itso))->display();
            }
    }
}


//methodes de la classe Menu

Menu::Menu(){                                   //constructeur par defaut
    Text *obj = new Text("Temperature :",0,0);
    string nom="Temperature";
    Screen* newScreen = new Screen(obj,nom);
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
    unsigned int i;

   mylcd.clear();
    for (i=currentScreen;(i<currentScreen+2 && i<nbscreens);i++){
        if(i==currentScreen){
            mylcd.setCursor(0,i-currentScreen);
            mylcd.print(">");
        }
         mylcd.setCursor(1,i-currentScreen);
         mylcd.print(screens[i]->getName());
    }
        
}

void Menu::enter(){ 
    mylcd.clear();
    screens[currentScreen]->display();
}

void Menu::back(){  
    currentScreen=0;
    display();
}

void Menu::next(){
 if(currentScreen<nbscreens) {
        currentScreen++;
    }
    display();
}

void Menu::prev(){
    if(currentScreen>0) {
        currentScreen--;
    }
    display();
}





