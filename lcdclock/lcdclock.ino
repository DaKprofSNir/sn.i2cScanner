/*---------------------------------------- 
  Programme complet i2c LCD+EEPROM+DS1307
  Auteurs des solutions : 
  clock et lcd: Sauvage Rullier
  eeprom: Douillère Sankara Boucard Porras
----------------------------------------*/
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd; // objet LCD Grove

// EEPROM decommenter la ligne du groupe   
//byte adresse[]={0x01,0x00}; // groupe G1
//byte adresse[]={0x02,0x00}; // groupe G2

// Nom de l'equipe taille max 16 caracteres
char message[]="Momopop's       ";

//registres DS1307   sec min heure l..d jour mois annee
byte ds1307reg[] = {0x00,0x28,0x12,0x01,0x17,0x02,0x19};

void setup(){
    Wire.begin();
    lcd.begin(16,2);
    Wire.begin();
    Serial.begin(9600);
    if(false){ // passer à true pour écrire l'EEPROM
        Wire.beginTransmission(0x50);
        Wire.write(adresse, sizeof(adresse) );
        Wire.write(message, sizeof(message) );
        Wire.endTransmission();
        Serial.print("graver "); Serial.println( message ); 
    }//END écrire l'EEPROM
    
    if(false){ // passer à true pour mettre a l'heure
        Wire.beginTransmission(0x68);              // Start
        Wire.write(0);                             // addresse du premier registre
        Wire.write(ds1307reg, sizeof(ds1307reg) );
        Wire.endTransmission();                    // Stop
        Serial.println("Mise à l'heure effectuee");
    }//END mettre a l'heure
    
    // effacer l'afficheur LCD 2x16 0123456789012345
    lcd.setCursor(0, 0); lcd.print("                ");
    lcd.setCursor(0, 1); lcd.print("                ");
}//END setup()

void loop(){
  //---- lire le nom de l'equipe dans l'EEPROM 
    Wire.beginTransmission(0x50);              // Start
    Wire.write(adresse, sizeof(adresse));      // addresse du premier registre
    Wire.endTransmission();                    // Stop
    Wire.requestFrom(0x50,sizeof(message));    // Start+lecture+stop 
    //----- recuperer le contenu du tampon ------------------- 
    for(byte i=0;i<sizeof(message);i++) message[i]=Wire.read();  

  //---- lire les registres du DS1307 horloge RTC 
	  Wire.beginTransmission(0x68);              // Start
    Wire.write(0);                             // addresse du premier registre
    Wire.endTransmission();                    // Stop
    Wire.requestFrom(0x68,sizeof(ds1307reg));  // Start+lecture+stop 
    //----- recuperer le contenu du tampon ------------------- 
    for(byte i=0;i<sizeof(ds1307reg);i++) ds1307reg[i]=Wire.read(); 
    
    //----- affichage si au moins 1 sec s'est ecoulee --------
    static byte last=0xFF;
    if( last!=ds1307reg[0] ){ last=ds1307reg[0];
        lcd.setRGB(random(255),random(255),random(255));
        lcd.setCursor(0, 1);
        lcd.print( ds1307reg[2],HEX ); lcd.print( ':');
        lcd.print( ds1307reg[1],HEX ); lcd.print( ':');
        lcd.print( ds1307reg[0],HEX ); lcd.print("   ");
	      lcd.setCursor(0, 1);
	      lcd.print(message);
    }//END if(last!=ds1307reg[0])
}//END loop()
