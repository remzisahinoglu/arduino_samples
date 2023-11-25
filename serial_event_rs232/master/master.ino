/*
bu program master arduino programıdır. pc den gelen verilerin ve komutların 
istenilen hücre(slave) arduinosuna gönderilmesinden ve hücre arduinolarından
gelen dataları bilgisayara aktarmasından sorumludur.

yazan: remzi şahinoğlu
tarih: 2.7.2015
*/

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // (RX, TX)

String inputString_pc = "";
String inputString_slave = "";

//********************** BAŞLANGIÇ AYARLARI *****************************//
void setup(){
  
  Serial.begin(9600);                                                    // Open serial communications and wait for port to open: 
  delay(500);
  inputString_pc.reserve(100);
  inputString_slave.reserve(100);
  mySerial.begin(9600);                                                  // set the data rate for the SoftwareSerial port
  
  Serial.println("master program starting...");                          // pc ye debug yap
  delay(500);
}

//********************** SERİ PORT KESMESİ ******************************//

void serialEvent() {
  while (Serial.available()) {                                           // bilgisayardan data geldiğinde
    Serial.println("pc den data geldi");
    char inChar_pc = (char)Serial.read(); 
    inputString_pc += inChar_pc;
    
    if(inputString_pc == "6"){
      mySerial.write('6');
      inputString_pc = "";                                               // bir sonraki değer için stringi boşalt
    }
    if(inputString_pc == "7"){
      mySerial.write('7');
      inputString_pc = "";
    }
    if(inputString_pc == "88"){
      mySerial.write("88");
      inputString_pc = "";
    }
    if(inputString_pc == "9"){
      mySerial.write('9');
      inputString_pc = "";
    }

  }
  while (mySerial.available()) {                                         // hücrelerden data geldiğinde
    Serial.println("hücreden den data geldi");
    char inChar_slave = (char)Serial.read(); 
    inputString_slave += inChar_slave;
  }
}


//************************** ANA PROGRAM ********************************//
void loop() {
  Serial.println("komut");
  delay(500);
  

  
  
  
  
  
  
  
  
}


