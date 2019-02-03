// test d'une eeprom 24c64
// le programme affiche ce qui se trouve dans l'adresse interne 0x0234
// puis incrémente ce nombre.
// et recommence ce cycle après 5 secondes

#include <Wire.h>

byte AdresseComposant =  0x50; // Adresse du composant I2C 1010xxx

uint16_t AdresseInterne = 0x0234; // l'adresse dedans l'EEPROM de 8192 octets 

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

//-- Ecrire 1 octet dans l'eeprom ----------------------------
void eeprom_write(byte composant, uint16_t cible, byte data) {
  Wire.beginTransmission(composant);
    Wire.write(cible >> 8);    // poid fort de l'adresse
    Wire.write(cible & 0xFF);  // poid faible de l'adresse
    Wire.write(data);
  Wire.endTransmission();
}

// lire 1 octet
byte eeprom_i2c_read(byte composant, uint16_t cible) {
    // Ecrire l'adresse cible dans le pointeur interne de l'eeprom 
    Wire.beginTransmission(composant);
      Wire.write(cible >> 8);    // poid fort de l'adresse
      Wire.write(cible & 0xFF);  // poid faible de l'adresse
    Wire.endTransmission();
    // lire 1 octet depuis le composant
    Wire.requestFrom(composant, 1);
    if(Wire.available())
        return Wire.read();
    else
        return 0;
}


void loop() {
    byte cerise = eeprom_i2c_read(AdresseComposant, AdresseInterne );
    Serial.print("Octet lu : "); Serial.println(cerise);
    cerise++;
    eeprom_write( AdresseComposant, AdresseInterne, cerise);
    delay(5000);
}
