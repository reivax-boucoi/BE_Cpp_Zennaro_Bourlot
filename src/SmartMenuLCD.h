#ifndef SMART_MENU_LCD_H
#define SMART_MENU_LCD_H

#include <unistd.h>
#include <vector>
#include "core_simulation.h"
#include "LCDObject.h"


class Screen{
protected:
    vector<ScreenObject*> objects;
    unsigned int currentObject;
    static unsigned int nbobjects;
    string name;
    
public:
    //Screen();
    Screen(ScreenObject*firstobj, string nom);
    void addObject(ScreenObject*newObj);
    void display();
    string getName();
    void Next();
    void Prev();

    friend class SmartMenuLCD;
};


class Menu{
private:
    vector<Screen*> screens;
    unsigned int currentScreen;
    static unsigned int nbscreens;
    
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
