#ifndef SMART_MENU_LCD_H
#define SMART_MENU_LCD_H
/*commented because it prevented proper project compilation
#include <unistd.h>
#include <vector>
#include "core_simulation.h"
#include "LCDObject.h"

class Screen: public ScreenObject{
protected:
    vector<ScreenObject> objects;
    int currentobject;
    string name;
    
public:
    Screen();
    void displayObj();
    ScreenObject* getPrev();
    ScreenObject* getNext();
};


class SmartMenuLCD: public Screen{
private:
    vector<Screen> screens;
    int currentScreen;
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
*/
#endif
