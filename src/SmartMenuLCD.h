#ifndef SMART_MENU_LCD_H
#define SMART_MENU_LCD_H

#include <unistd.h>
#include <vector>
#include "core_simulation.h"

class Screen{
private:
    
public:
    Screen();
};


class SmartMenuLCD{
private:
    vector<Screen> screens;
    int currentScreen=0;
    bool screenSelected=false;
    
public:
    SmartMenuLCD();
    void addScreen(Screen s);
    void display();
    void enter();
    void back();
    void next();
    void prev();
};

#endif
