#include "LCDObject.h"


LCD myLcd;

ScreenObject::ScreenObject(int x, int y){
    this->x=x;
    this->y=y;
}


Value::Value(float *ptr, int x, int y, int nbDigits):ScreenObject(x,y){
    this->nbDigits=nbDigits;
    valptr=ptr;
}
void Value::display(void){
    myLcd.setCursor(x,y);
    setDPpos();
    myLcd.print(*valptr,DPpos);
}

void Value::setDPpos(void){ //TODO generalize this for any length number
if ( (*valptr) < 10.0) {
    DPpos = nbDigits - 1;
  } else if ((*valptr) < 100.0) {
    DPpos = nbDigits - 2;
  } else {
    DPpos = 1;
  }
}

EditableValue::EditableValue(float *ptr, int x, int y, int nbDigits, int min, int max):Value(ptr,x,y,nbDigits){
    minVal=min;
    maxVal=max;
    cursorPos=0;
}

bool EditableValue::advanceCursor(void){
  cursorPos++;
  if (cursorPos >= nbDigits){
      cursorPos = 0;
      return true;
  }
  return false;
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

