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
0(RX)       1(RO)
1(TX)       4(DI)
2           2(RE),3(DE)
GND         5(GND)
+5V         8(VCC)
            7(B)-rx     diğer modülün 7(B) hattına
            8(A)-tx     diğer modülün 8(A) hattına
            
*/

//---------------------------- DEĞİŞKENLER -------------------------------//
String inputString = "";                                                  // reçete bilgileri bu stringe yazılır
int stringComplete = 0;

//---------------------- BAŞLANGIÇ AYARLARI ------------------------------//
void setup() {
   delay(1000);
   Serial.begin(9600);
   delay(1000);

   pinMode(13, OUTPUT);
   pinMode(2, OUTPUT);                                                    // re(not)(2) ve de(3) pinleri (MAX485)
   pinMode(7, INPUT_PULLUP);
   delay(100);
   digitalWrite(2, HIGH);                                                 // transmit aktif, recive kapalı
   digitalWrite(13, LOW);
   
}

//-------------------------- ANA PROGRAM ---------------------------------//
void loop() {
   if(digitalRead(7) == 0)
   {
     //digitalWrite(13, HIGH);
     //delay(1000);                                                           // hayati önemli
     digitalWrite(2 ,HIGH);                                                 // recive pasif, transmit açık
     //delay(1);
     Serial.println("arfesan a.s.");
     Serial.flush();                                                        // transmit bufferın bitmesini bekle
     //delay(1);
     digitalWrite(2 ,LOW);                                                  // recive aktif, transmit kapalı
     //digitalWrite(13, LOW);
   }
   //delay(100);
}










