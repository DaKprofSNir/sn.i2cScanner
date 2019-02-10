/*------------- Démo Afficheur 2 lignes Grove ---------*/
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd; 
char message[]="SNir"; // taille max 20 caracteres

void setup(){
    Wire.begin();
    lcd.begin(16, 2);
}//END setup()

void loop(){
  //---- un peu de couleur
	lcd.setRGB(random(255),random(255),random(255));

  //---- ecrire sur la premiere ligne
	lcd.setCursor(0, 0);
	lcd.print(message);
	lcd.print(" ");
	lcd.print(random(255));

  //---- ecrire sur la deuxieme ligne
	lcd.setCursor(0, 1);
	lcd.print("Hello les SN");
	delay(1000);
}//END loop()
