#include <Wire.h>

char message[32]="CIEL SNir";
byte adresse[]={0x00,0x00}; // adresse du premier octet du message gravé dans l'EEPROM

void setup(){
	delay(5000); // parachute
  Serial.begin(9600);
	Wire.begin();
}//setup()

void loop(){
	if(Serial.available()) switch(Serial.read()){
		case 'L': case 'l': case 'R': case 'r' : 
			Serial.println("Lecture dans l'EEPROM i2c");
			LectureEEPROM(); 
			Serial.println("message");
			break;
		case 'E': case 'e': case 'W': case 'w' : 
			Serial.println("Ecriture dans l'EEPROM i2c");
			strcpy(message,"Nouveau texte");
			EcritureEEPROM(); 
			break;
	}//if(Serial)switch()
}//loop()
  
void LectureEEPROM(){
	Wire.beginTransmission(0x50);  						//start + @i2c avec bit écriture
	Wire.write(adresse, sizeof(adresse) ); 		//adresse visée dedans l'EEPROM
	Wire.endTransmission(); 							    //stop
	Wire.requestFrom(0x50,sizeof(message));   //Start + @i2c avec bit lecture + lecture + stop 
	for(byte i=0;i<sizeof(message);i++) message[i]=Wire.read(); // recupere le contenu du tampon	  
}//LectureEEPROM()
	
void EcritureEEPROM(){
	Wire.beginTransmission(0x50);			      //start + @i2c avec bit écriture
	Wire.write(adresse, sizeof(adresse) );  //adresse visée dedans l'EEPROM
	Wire.write(message, sizeof(message) );	//les octets à graver dans l'EEPROM
	Wire.endTransmission();					        //stop
}//EcritureEEPROM()
