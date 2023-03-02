#include <arduino.h>
#include "i2cScan.h"
#include <Wire.h>

void i2cScan(){
      int i2c[128];
      byte error, address;
      int nDevices = 0;
      static int passe=0;
     
      SerialScan.println("\n\nI2C Scanner"); 
      SerialScan.print("   passe "); SerialScan.print(++passe);
      SerialScan.print("\n ");
      for(address = 1; address < 127; address++ ){
          Wire.beginTransmission(address);
          i2c[address] = (Wire.endTransmission() == 0);
          if( i2c[address] ){
             SerialScan.print("x");
             nDevices++;
          }else{
             SerialScan.print(".");
          }
          if(address%32 == 0) SerialScan.println("");    
      }
      
      SerialScan.println("");
      if( nDevices==0 ){
         SerialScan.println("No I2C devices found\n");
      }else{
         for(address = 1; address < 127; address++ ) if( i2c[address] ){
            SerialScan.print("I2C device found at address 0x");
            if (address<16) SerialScan.print("0");
            SerialScan.print(address,HEX);
            //--- adresse connue ?
            if( 0x19 == address       ) SerialScan.print("  LSM303  Accéléromètre+Boussole");
            if( 0x1F == (address|0x1) ) SerialScan.print("  LSM9D50 Gyroscope+Accéléromètre");
            if( 0x3D == (address|0x1) ) SerialScan.print("  SSD1306 OLED 128x64");
            if( 0x5C == address       ) SerialScan.print("  DHT12  Temp & Humidity");
            if( 0x68 == address       ) SerialScan.print("  DS1307 RTC");
            if( 0x27 == (address|0x7) ) SerialScan.print("  PCF8574 /LCD interface");
            if( 0x57 == (address|0x7) ) SerialScan.print("  24Cxx EEPROM");
            if( 0x43 == (address|0x3) ) SerialScan.print("  INA219 Current and Voltage Sensor");
            SerialScan.println("");    
         }
      }




  
}
