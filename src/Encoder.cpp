#include "Encoder.h"


char getEncoderValue(void){
    char res;
    cin>>res;
    if(res=='+' || res=='-' || res=='e' || res=='b')return res;
    return 0;
}
