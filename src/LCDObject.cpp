#include "LCDObject.h"



ScreenObject::ScreenObject(int x, int y){
    this.x=x;
    this.y=y;
}


Value::Value(float *ptr, int x, int y, int resolution)ScreenObject(x,y){
    this.resolution=resolution;
    valptr=ptr;
}
void Value::display(void){
    
}
