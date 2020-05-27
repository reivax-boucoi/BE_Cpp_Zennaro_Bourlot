#ifndef SMART_MENU_LCD_H
#define SMART_MENU_LCD_H

#include <unistd.h>
#include <vector>
#include "core_simulation.h"
#include "LCDObject.h"

//classe Screen
class Screen{
protected:
    vector<ScreenObject*> objects;
    unsigned int currentObject;
    unsigned int nbobjects=0;
    string name;
    bool editing=false;
    int prevx=-1;
    int prevy=-1;
    unsigned int prev_obj=100;
    
public:
    Screen(ScreenObject*firstobj, string nom);
    void addObject(ScreenObject*newObj);
    void display();
    string getName();
    void Next();
    void Prev();
    void enter();
    void back();

};

//classe relative au menu principal
class Menu{
private:
    vector<Screen*> screens;
    unsigned int currentScreen;
    unsigned int nbscreens=0;
    bool screenEntered=false;
    int tmp=0;
    
public:
    Menu(Screen *s);
    void addScreen(Screen *s);
    void display();
    void enter();
    void back();
    void next();
    void prev();
};

#endif
