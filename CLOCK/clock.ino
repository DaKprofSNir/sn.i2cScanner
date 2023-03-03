/*---------------------------------------- 
  Programme complet i2c OLED+EEPROM+DS1307
  Auteurs des solutions : 
----------------------------------------*/
#include <Wire.h>
#include <Adafruit_SH110X.h>

#define OLED_i2c_Addr 0x3c  //initialise avec l'adresse 0x3C (typiquement OLED chinois)
//#define OLED_i2c_Addr 0x3d //initialise avec l'adresse 0x3D (typiquement OLED Adafruit)

#define SCREEN_WIDTH 128  // Largeur en pixels
#define SCREEN_HEIGHT 64  // hauteur en pixels
#define OLED_RESET -1     // Pas de broche reset sur ce module
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// eeprom DECOMMENTEZ la ligne du groupe
byte adresse[] = { 0x01, 0x00 };  // groupe G1
//byte adresse[]={0x02,0x00}; // groupe G2

// Nom de l'equipe centré et de taille exactement 21 caracteres + zero terminal
//             "012345678901234567890"
char message[]="    Lapins Blancs    \0";

//registres DS1307 au format BCD => 0x09 + 1 ==> 0x10 et non 0xA0 ! et 0x59 + 1 ==> 0x00 on repasse à zéro après 59 secondes
//                  sec   min   heure l..d  jour  mois  annee
byte ds1307reg[]={ 0x00, 0x41, 0x13, 0x01, 0x05, 0x04, 0x24 };

// declaration de la barre 4 boutons sur les broches 3 à 7 pour la mise à l'heure 
enum {pinBPminute=3, pinBPheure, pinBPjour, pinBPRaz, pinGND};

void setup() {
  delay(1000);  // parachute + OLED power up

  pinMode(pinGND, OUTPUT); digitalWrite(pinGND, LOW);
  pinMode(pinBPRaz, INPUT_PULLUP);
  pinMode(pinBPjour, INPUT_PULLUP);
  pinMode(pinBPheure, INPUT_PULLUP);
  pinMode(pinBPminute, INPUT_PULLUP);
  
  Wire.begin();
  Wire.setClock(400000L);  // optionnel. par défaut la vitesse i2c est 100kbps.
  Serial.begin(9600);
  display.begin(OLED_i2c_Addr, true);

  if(false){ // passer à true pour écrire l'EEPROM avec le message personnalisé
    Wire.beginTransmission(0x50);
    Wire.write(adresse, sizeof(adresse));
    Wire.write(message, sizeof(message));
    Wire.endTransmission();
    Serial.print("graver ");
    Serial.println(message);
    while(true);
  }//END écrire l'EEPROM

  if(false){ // passer à true pour mettre a l'heure
    Wire.beginTransmission(0x68);  // Start
    Wire.write(0);                 // addresse du premier registre
    Wire.write(ds1307reg, sizeof(ds1307reg));
    Wire.endTransmission();  // Stop
    Serial.println("Mise à l'heure effectuee");
    while (true);
  }//END mettre a l'heure

  // effacer l'afficheur OLED
  display.clearDisplay();
}//END setup()

void loop(){
  //---- lire le nom de l'equipe dans l'EEPROM
  Wire.beginTransmission(0x50);             // Start
  Wire.write(adresse, sizeof(adresse));     // addresse du premier registre
  Wire.endTransmission();                   // Stop
  Wire.requestFrom(0x50, sizeof(message));  // Start+lecture+stop
  //----- recuperer le contenu du tampon -------------------
  for(byte i=0; i<sizeof(message); i++) message[i]=Wire.read();

  //---- lire les registres du DS1307 horloge RTC
  Wire.beginTransmission(0x68);               // Start
  Wire.write(0);                              // addresse du premier registre
  Wire.endTransmission();                     // Stop
  Wire.requestFrom(0x68, sizeof(ds1307reg));  // Start+lecture+stop
  //----- recuperer le contenu du tampon -------------------
  for (byte i=0; i<sizeof(ds1307reg); i++) ds1307reg[i]=Wire.read();

  //----- affichage si au moins 1 sec s'est ecoulee --------
  static byte last = 0xFF;
  if(last!=ds1307reg[0]){ last = ds1307reg[0];
    display.clearDisplay();
    display.setCursor(0, 0); // pixel 0,0 en haut à gauche
    display.setTextColor(SH110X_BLACK, SH110X_WHITE);  // texte noir sur blanc
    display.setTextSize(1);
    display.print(message);

    display.setCursor(16, 14); //16 pixel à gauche, 14 pixels vers le bas
    display.setTextColor(SH110X_WHITE);
    display.setTextSize(2);
    display.print(ds1307reg[4],HEX);
    display.print('/');
    display.print(ds1307reg[5],HEX);
    display.print("/20");
    display.print(ds1307reg[6],HEX);
    display.print(' ');

    display.setCursor(0, 38);  //0 pixel à gauche,38 pixels vers le bas
    display.setTextSize(3);
    display.print(ds1307reg[2]<10?"0":"");
    display.print(ds1307reg[2],HEX);
    display.print(':');
    display.print(ds1307reg[1]<10?"0":"");
    display.print(ds1307reg[1],HEX);

    display.setTextSize(2);
    display.print(' ');
    display.print(ds1307reg[0]<10?"0":"");
    display.print(ds1307reg[0],HEX);

    display.display();
  }//END if(last!=ds1307reg[0])

  // mise à l'heure par la barre de 4 boutons
  static byte BPRaz,BPjour,BPheure,BPminute=BPheure=BPjour=BPRaz=HIGH;
  #define WRDS1307 {Wire.beginTransmission(0x68); Wire.write(0); Wire.write(ds1307reg,sizeof(ds1307reg)); Wire.endTransmission();}
  if( BPRaz!=digitalRead(pinBPRaz) ) if( (BPRaz=digitalRead(pinBPRaz)) ){
      ds1307reg[0]=0x00; ds1307reg[1]=0x41; ds1307reg[2]=0x13; ds1307reg[3]=0x01; ds1307reg[4]=0x05; ds1307reg[5]=0x03; ds1307reg[6]=0x23;
      WRDS1307;
  }//BPRaz

  if( BPjour!=digitalRead(pinBPjour) ) if( (BPjour=digitalRead(pinBPjour)) ){
      if( (++ds1307reg[4]&0x0F)>9 ) if( (ds1307reg[4]+=6)>0x31 ) ds1307reg[4]=0x01;
      WRDS1307;
  }//BPjour

  if( BPheure!= digitalRead(pinBPheure) ) if( (BPheure=digitalRead(pinBPheure)) ){
      if( (++ds1307reg[2]&0x0F)>9 ) if( (ds1307reg[2]+=6)>=0x23 ) ds1307reg[2]=0x00;
      WRDS1307;      
  }//BPmois

  if( BPminute!=digitalRead(pinBPminute) ) if( (BPminute=digitalRead(pinBPminute)) ){
      if( (++ds1307reg[1]&0x0F)>9 ) if( (ds1307reg[1]+=6)>=0x59 ) ds1307reg[1]=0x00;
      WRDS1307;      
  }//BPmois

}//END loop()
