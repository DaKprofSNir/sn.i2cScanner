template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; } 
#include <RTClib.h>

RTC_DS1307 rtc;

void setup(){
  delay(1000); // parachute 
  Serial.begin(9600);
  if(!rtc.begin())while(true)Serial<<"RTC introuvable.\n";
  if(!rtc.now().isValid()){ 
      Serial << "Mise à l'heure à la date de compilation.\n";
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }else{
      Serial << "Date sauvegardée par batterie.\n";
   }
}//setup()

void loop () {
   DateTime now = rtc.now();
   char buffer[] = "DD/MM/YYYY hh:mm:ss"; // on initialise un buffer avec le format à utiliser
   now.toString(buffer);
   Serial << "Date & Heure : " << buffer << '\n' ;
   delay(1000);
}//loop()
