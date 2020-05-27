#include "LCDObject.h"

LCD myLcd;

ScreenObject::ScreenObject(int x, int y){
    this->x=x;
    this->y=y;
}

int ScreenObject::getx(){
    return x;
};
int ScreenObject::gety(){
    return y;
};

Value::Value(float *ptr, int x, int y, int nbDigits):ScreenObject(x,y){
    this->nbDigits=nbDigits;
    valptr=ptr;
}
void Value::display(void){
    myLcd.setCursor(x,y);
    setDPpos();
    myLcd.print(*valptr,DPpos);
}

void EditableValue::display(void){
    myLcd.setCursor(x,y);
    setDPpos();
    myLcd.print(currentValue,DPpos);
    
    myLcd.blink(editing);                    //blink if value is being edited
    if ((nbDigits - DPpos) <= cursorPos) {   //reset cursor to editing value
      myLcd.setCursor(x + cursorPos + 1, y); // offset for comma symbol
    } else {
      myLcd.setCursor(x + cursorPos, y);    //no offset
    }
}

void Value::setDPpos(void){ //TODO generalize this for any length number
if ( (*valptr) < 10.0) {
    DPpos = nbDigits - 1;
  } else if ((*valptr) < 100.0) {
    DPpos = nbDigits - 2;
  } else if ((*valptr) < 1000.0) {
    DPpos = nbDigits - 3;
  } else if ((*valptr) < 10000.0) {
    DPpos = nbDigits - 4;
  } else {
    DPpos = 1;
  }
}

EditableValue::EditableValue(float *ptr, int x, int y, int nbDigits, int min, int max):Value(ptr,x,y,nbDigits){
    minVal=min;
    maxVal=max;
    cursorPos=0;
    currentValue=*ptr;
}

void EditableValue::advanceCursor(void){
    if(!editing){   //enter editing mode
        editing=true;
        cursorPos=0;    //reset cursorPos
    }else{
        cursorPos++;
        if (cursorPos >= nbDigits){//wrap around and exit editing mode
            cursorPos = 0;
            (*valptr)=currentValue  ;       //update real value with temporary edited value when exiting editing mode
            editing=false;
        }
    }
    myLcd.setCursor(x+cursorPos,y);   //reset cursor to editing value
}

void EditableValue::increment(void) {
  int p = nbDigits - DPpos - 1 - cursorPos;
  currentValue +=  pow(10, p);
  if (currentValue > maxVal)currentValue = maxVal;
}

void EditableValue::decrement(void) {
  int p = nbDigits - DPpos - 1 - cursorPos;
  currentValue -=  pow(10, p);
  if (currentValue < minVal)currentValue = minVal;
}

void EditableValue::setEditing(bool edit){
    editing=edit;
}

Text::Text(string str, int x, int y):ScreenObject(x,y){
    this->str=str;
}

void Text::display(void){
    myLcd.setCursor(x,y);
    myLcd.print(str);
}

string Text::getCurrentText(void){
    return str;
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

