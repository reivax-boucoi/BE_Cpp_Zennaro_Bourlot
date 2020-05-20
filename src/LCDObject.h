#ifndef LCD_OBJECT_H
#define LCD_OBJECT_H

#include <unistd.h>
#include <vector>
#include <iterator>
#include "core_simulation.h"

class ScreenObject {
protected:
    int x;
    int y;
    virtual void display(void)=0;
public:
    ScreenObject(int x, int y);
};

class Value : public ScreenObject{
protected:
    float *valptr;
    int resolution;
public:
    Value(float *ptr, int x, int y, int resolution);
    void display(void);
};


class EditableValue : public Value{
private:
    float currentValue;
    float minVal;
    float maxVal;
    int currentDecade;
public:
    EditableValue(float *ptr, int x, int y, int resolution, int min, int max);
    bool nextDecade(void);
    
    
};


class Text : public ScreenObject{
protected:
    string str;
public:
    Text(string str, int x, int y);
    void display(void);
};


class EditableText : public Text{
private:
    vector<string> texts;
    vector<string>::iterator it;
    int width;
public:
    EditableText(int x, int y, int width);
    EditableText(string str, int x, int y, int width);
    void addText(string str);
    void next(void);
    void prev(void);
};

#endif
