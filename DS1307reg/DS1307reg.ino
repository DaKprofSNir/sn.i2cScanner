#include <Wire.h>

//registres DS1307   sec min heure l..d jour mois annee
byte ds1307reg[] = {0x00,0x20,0x14,0x03,0x08,0x03,0x23};

void setup() {
    Wire.begin();
    Serial.begin(9600);
    if( false ){ // passer à true pour mettre a l'heure
        Wire.beginTransmission(0x68);              // Start
        Wire.write(0);                             // addresse du premier registre
        Wire.write(ds1307reg, sizeof(ds1307reg) );
        Wire.endTransmission();                    // Stop
        Serial.println("Mise à l'heure effectuee");
    }
}//END setup

void loop(){
	  //----- lecture des registres du DS1307 RTC --------------
    Wire.beginTransmission(0x68);              // Start
    Wire.write(0);                             // pointer l'addresse du premier registre
    Wire.endTransmission();                    // Stop
	  Wire.requestFrom(0x68,sizeof(ds1307reg));  // Start+lecture+stop 
	  
    //----- recuperer le contenu du tampon ------------------- 
    for(byte i=0;i<sizeof(ds1307reg);i++) ds1307reg[i]=Wire.read(); 
	
    //----- affichage si au moins 1 sec s'est ecoulee --------
    static byte last=0xFF;
    if( last!=ds1307reg[0]){ last=ds1307reg[0];
        switch( ds1307reg[4] ){
        case 1 : Serial.print("Lundi "); break;
        case 2 : Serial.print("Mardi "); break;
        case 3 : Serial.print("Mercredi "); break;
        case 4 : Serial.print("Jeudi "); break;
        case 5 : Serial.print("Vendredi "); break;
        case 6 : Serial.print("Samedi "); break;
        case 7 : Serial.print("Dimanchedi "); break;
        default: Serial.print("Bizarredi "); break;
        }
        Serial.print( ds1307reg[4],HEX ); Serial.print("/");
        Serial.print( ds1307reg[5],HEX ); Serial.print("/20");
        Serial.print( ds1307reg[6],HEX ); Serial.print("  ");

        Serial.print( ds1307reg[2],HEX ); 
        Serial.print( ':');
        Serial.print( ds1307reg[1],HEX ); 
        Serial.print( ':');
        Serial.print( ds1307reg[0],HEX ); 
        Serial.println();
    }//------------------------------------------------------
}//END loop
