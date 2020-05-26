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
    
public:
    Screen(ScreenObject*firstobj, string nom);
    void addObject(ScreenObject*newObj);
    void display();
    string getName();
    void Next();
    void Prev();

    friend class SmartMenuLCD;
};

//classe relatif au menu principale
class Menu{
private:
    vector<Screen*> screens;
    unsigned int currentScreen;
    unsigned int nbscreens=0;
    
public:
    Menu();
    Menu(Screen *s);
    void addScreen(Screen *s);
    void display();
    void enter();
    void back();
    void next();
    void prev();
};

#endif
