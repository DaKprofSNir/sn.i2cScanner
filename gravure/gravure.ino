

void setup() {
    Serial.begin(9600);
}

void loop() {
    byte i, octet;
  
    //--------Lecture d'une chaine de caractères octet par octet --------
    Serial.println("Lecture d'une chaine de caractères octet par octet :");
    byte chaine[]="Nom de l'Equipe\0";
    for(i=0; chaine[i]!=0; i++){
        octet = chaine[i];
        //
        // ici vous pouvez envoyer octet vers l'eeprom
        //
        Serial.print((char)octet);
    }
    Serial.println("");

    //---------Construction d'une chaine de caractères octet par octet-----
	Serial.println("Construction d'une chaine de caractères octet par octet :");
    byte Relecture[100]={0};
    for( i=0; i<=10; i++){
       //
       octet = i+'a'; // ou octet lu depuis une eeprom)
       //
       Relecture[i++]=octet;
    }
    Relecture[i++]=0; // pour terminer la chaine de caracteres
    Serial.println( (char*)Relecture);
    
    delay(5000);
}
