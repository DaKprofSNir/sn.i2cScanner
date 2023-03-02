#include <Wire.h>
#include <Adafruit_SH110X.h>

#define OLED_i2c_Addr 0x3c //initialise avec l'adresse 0x3C (typiquement OLED chinois)
//#define OLED_i2c_Addr 0x3d //initialise avec l'adresse 0x3D (typiquement OLED Adafruit)

#define SCREEN_WIDTH 128 // Largeur en pixels
#define SCREEN_HEIGHT 64 // hauteur en pixels
#define OLED_RESET    -1 // Pas de broche reset sur ce module
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()   {
  delay(1000); // parachute + OLED power up
  Wire.begin();
  Wire.setClock(400000L); // optionnel. par défaut la vitesse i2c est 100kbps.
  Serial.begin(9600);
  display.begin(OLED_i2c_Addr, true);
  display.clearDisplay();
}//setup()


void loop(){
  static long i=1234567;
  display.clearDisplay();
  display.setCursor(0, 0);
  
  display.setTextColor(SH110X_BLACK, SH110X_WHITE); // texte noir sur blanc
  //                                      "012345678901234567890"
  display.setTextSize(1); display.println(" Hey les p'tits loups\n");
  
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1); display.println("012345678901234567890");
  display.setTextSize(2); display.println("0123456789");
  display.setTextSize(3); display.println(i++);
  
  display.display();
}//loop()
