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
    string name;
    
public:
    Screen();
    Screen(ScreenObject*firstobj);
    void display();
    ScreenObject* getPrev();
    ScreenObject* getNext();

    friend class SmartMenuLCD;
};


class SmartMenuLCD{
private:
    vector<Screen*> screens;
    unsigned int currentScreen;
    static unsigned int nbscreens;
    bool screenSelected=false;
    
public:
    SmartMenuLCD();
    SmartMenuLCD(Screen *s);
    void addScreen(Screen *s);
    void display();
    void enter();
    void back();
    void next();
    void prev();
};

#endif
