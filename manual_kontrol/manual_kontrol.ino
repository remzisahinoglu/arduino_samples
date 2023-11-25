/*
prg adı: kalite_soguk_test_v3
board: arduino uno r3
tarih: 22.4.2016
yazan: Remzi ŞAHİNOĞLU

bu program soğuk testini bilgisayardan yapıyoruz ya, he, işte 
bilgisayar olmaz ise bu programa test yükleyip sonra soğuk testi 
arduinosuna datalar aktarılabilir.

*/

#include <SoftwareSerial.h>

int aktif_arduino = 0;
int aktif_pc = 0;
String inputString = "";

//------------------------------ GİRİŞLER --------------------------------//
// digital 0:RX, 1:TX olarak serial tanımlanmıştır
SoftwareSerial mySerial(2, 3); // (RX, TX)                                // sayac için kondu

//---------------------- KONFİGÜRASYON AYARLARI --------------------------//
void setup() 
{
  Serial.begin(9600);                                       // initialize serial: 19200 bit per second 
  delay(1000);
  mySerial.begin(9600);
  delay(1000);

  Serial.println("OK");
}

void serialEvent() {
  while (Serial.available())                                             // bufferda okuacak veri olduğu sürece tek tek byte ları oku
  {
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    aktif_arduino = 1;
  }
}

//------------------------------------------------------------------------//
//-------------------------- ANA PROGRAM ---------------------------------//
void loop() 
{
  while (mySerial.available())                                             // bufferda okuacak veri olduğu sürece tek tek byte ları oku
  {
    char inChar = (char)mySerial.read(); 
    inputString += inChar;
    aktif_pc = 1;
  }

  delay(100);

  if(aktif_pc == 1)
  {
    aktif_pc = 0;
    Serial.println(inputString);
    inputString = "";
  }
  
  delay(100);
  
  if(aktif_arduino == 1)
  {
    aktif_arduino = 0;
    mySerial.println(inputString);
    inputString = "";
  }
  delay(100);
}





