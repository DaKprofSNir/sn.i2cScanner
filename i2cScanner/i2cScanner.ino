#include "i2cScan.h"   
#include <Wire.h>
     
     
void setup(){
    delay(1000); //parachute
    Wire.begin();
    Serial.begin(9600);
}//setup();
  
void loop(){
   i2cScan();
   delay(5000);           // wait 5 seconds for next scan
}///loop
