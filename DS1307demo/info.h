/*
Mise à l'heure/lecture d'une horloge RTC DS1307
Version avec la librairie RTClib

Le module contient deux composants I2C :
- RTC DS1307 à l'adresse 0x68
- EEPROM 24L32 à l'adresse 0x50

Connection Arduino vers module:
GND <----> GND
VCC <----> VCC
SDA <----> SDA
SCL <----> SCL
*/