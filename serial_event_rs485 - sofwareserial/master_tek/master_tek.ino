/*
yazan: remzi şahinoğlu
tarih: 17.103.2016
board: arduino uno

bu program rs485 protokolü için yazılmış olup rs485 modulu ile bağlantısı yapılmıştır.
data göndermek için modülün 2.ve 3.pini HIGH yapıldığında gönderim aktif alım pasif
LOW yapıldığında gönderim pasif alım aktif olmaktadır.

bu program sadece belirli periyotta data göndermektedir.

arduino     485modül
-------     --------
0(RX)       pc
1(TX)       pc
3(sRX)      1(RO)
4(sTX)      4(DI)
5           2(RE),3(DE)
GND         5(GND)
+5V         8(VCC)
            7(B)-rx     diğer modülün 7(B) hattına
            8(A)-tx     diğer modülün 8(A) hattına
            
*/

#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 4); // (RX, TX)

//********************** BAŞLANGIÇ AYARLARI *****************************//
void setup()
{
  delay(100);
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);

  pinMode(5, OUTPUT);                                                    // re(not)(2) ve de(3) pinleri (MAX485)
  delay(100);
  digitalWrite(5, LOW);                                                  // recive aktif, transmit kapalı
}

//************************** ANA PROGRAM ********************************//
void loop()
{
  while (mySerial.available())                                           // pc den istasyona data gönder
  {   
    Serial.print((char)mySerial.read()); 
  }
  delay(1);
}









