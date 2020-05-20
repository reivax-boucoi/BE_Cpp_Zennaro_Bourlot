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
    cout << "set cursor "<<x<<" and "<<y<<endl;
    myLcd.setCursor(x,y);
    myLcd.print(*valptr,resolution);
}


EditableValue::EditableValue(float *ptr, int x, int y, int resolution, int min, int max):Value(ptr,x,y,resolution){
    minVal=min;
    maxVal=max;
    currentDecade=0;
}
