#include <Wire.h>

char message[21]="CIEL SNir"; // taille max 20 caracteres + \0
//byte adresse[]={0x01,0x00}; // groupe G1
//byte adresse[]={0x02,0x00}; // groupe G2

void setup(){
    Wire.begin(); // initialise the connection
    Serial.begin(9600);
	  if( false ){ // passer à true pour écrire
		    Wire.beginTransmission(0x50);
		        Wire.write(adresse, sizeof(adresse) );
		        Wire.write(message, sizeof(message) );
		    Wire.endTransmission();
        Serial.print("graver "); Serial.println( message ); 
        while(true);
	  }
}//setup()

void loop(){
	  // lecture EEPROM
    Wire.beginTransmission(0x50);
        Wire.write(adresse, sizeof(adresse) );
    Wire.endTransmission();
	  Wire.requestFrom(0x50,sizeof(message));      // Start+lecture+stop 
	  for(byte i=0;i<sizeof(message);i++) message[i]=Wire.read(); // recupere le contenu du tampon	  
	  Serial.println( message ); 
	  delay(500);
}//loop()
