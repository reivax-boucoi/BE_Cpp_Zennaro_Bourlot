#ifndef LCD_OBJECT_H
#define LCD_OBJECT_H

#include <unistd.h>
#include <vector>
#include <iterator>
#include "core_simulation.h"
#include "math.h"

class ScreenObject {        //holds objects present on a screen : Text, Value, EditableText, EditableValue
protected:
    int x;
    int y;
public:
    virtual void display(void)=0;
    int getx(){return x;};
    int gety(){return y;};
    ScreenObject(int x, int y);
};

class Value : public ScreenObject{
protected:
    float *valptr;
    int nbDigits;                 //the length of the number in chars(fixed so not to overlap any other chars)
    int DPpos;                   //decimal point position
    void setDPpos(void);        //updates DPpos based on current value && nbDigits required : changes resolution
public:
    Value(float *ptr, int x, int y, int nbDigits);
    void display(void);
};


class EditableValue : public Value{
private:
    float currentValue;                //currently shown value, is different from the pointed value during editing
    float minVal;                     //bounds for editing the value
    float maxVal;
    int cursorPos=0;
    bool editing=false;
public:
    EditableValue(float *ptr, int x, int y, int nbDigits, int min, int max);
    void advanceCursor(void);          //select the next decade to edit or exit editing mode
    void increment(void);             // increment the selected decade
    void decrement(void);            // "" ""
    void display(void);
    
};


class Text : public ScreenObject{
protected:
    string str;                  //displayed text
public:
    Text(string str, int x, int y);
    void display(void);
};


class EditableText : public Text{
private:
    vector<string> texts;             //vector of possible texts
    vector<string>::iterator it;     //current displayed text
    int width;                      //nb char width (fixed so not to overlap any other chars)
public:
    EditableText(int x, int y, int width);
    EditableText(string str, int x, int y, int width);
    void addText(string str);
    void next(void);                 //cycle through texts
    void prev(void);                // "" ""
};  

#endif
