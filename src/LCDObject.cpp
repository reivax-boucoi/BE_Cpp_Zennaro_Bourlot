#include "LCDObject.h"


LCD myLcd;

ScreenObject::ScreenObject(int x, int y){
    this->x=x;
    this->y=y;
}


Value::Value(float *ptr, int x, int y, int resolution):ScreenObject(x,y){
    this->resolution=resolution;
    valptr=ptr;
}
void Value::display(void){
    myLcd.setCursor(x,y);
    myLcd.print(*valptr,resolution);
}


EditableValue::EditableValue(float *ptr, int x, int y, int resolution, int min, int max):Value(ptr,x,y,resolution){
    minVal=min;
    maxVal=max;
    currentDecade=0;
}



Text::Text(string str, int x, int y):ScreenObject(x,y){
    this->str=str;
}

void Text::display(void){
    myLcd.setCursor(x,y);
    myLcd.print(str);
}



EditableText::EditableText(int x, int y, int width):Text("",x,y){
    this->width=width;
}


EditableText::EditableText(string str, int x, int y, int width):Text(str,x,y){
    this->width=width;
    addText(str);
}

void EditableText::addText(string str){
    
    str.resize (width,' ');
    if(texts.empty()){
        this->str=str;
    }
    texts.push_back(str);
    it=texts.begin();
    
}

void EditableText::next(void){
    if(texts.empty())return;
    ++it;
    if(it==texts.end())it=texts.begin();
    str=*it;
}

void EditableText::prev(void){
    if(texts.empty())return;
    if(it==texts.begin())it=texts.end();
    --it;
    str=*it;
}

