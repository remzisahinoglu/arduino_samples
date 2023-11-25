/*
prg adı: master_switch_programi
board: arduino uno r3
tarih: 14.7.2015
yazan: Remzi ŞAHİNOĞLU

bu program pc den gelen reçete bilgilerinin, manuel komutların ve test
durum bilgilerinin pcden istasyonlara,istasyonlardan pcye aktarılmasnı
sağlar. her komutun başındaki ilk byte istasyon bilgisini temsil eder.
istasyon bilgisi okunduktan sonra demux ayarlanır.  reçete veya manuel
bilgiler ondan sonra okunduğu gibi yollanır.istasyondan gelen bilginin 
ilk byteı ise yine istasyon bilgisini temsil eder. bu bilgi diğer test
durum bilgileriyle birlikte pcye gönderilir. pc deki  arayüz tarafında
bu bilgi ayırt edilerek istenilen istasyon databaseinde saklanır.
*/

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // (RX, TX)

//------------------------------ ÇIKIŞLAR --------------------------------//
const int S4 = 4;                                                         // 
const int S5 = 5;
const int S6 = 6;
const int S7 = 7;

const int S0 = 8;                                                         // S0(10.pin) demux en düşük biti
const int S1 = 9;                                                         // S1(11.pin)
const int S2 = 10;                                                        // S2(14.pin)
const int S3 = 11;                                                        // S3(13.pin) demux en yüksek biti

//---------------------------- DEĞİŞKENLER -------------------------------//
String inputString_pc = "";                                               // pc den gelen dataların tutulduğu string
String inputString_istasyon = "";                                         // istasyonlardan gelen dataların tutulduğu string

unsigned int select_active = 1;                                           // pc den gelen ilk komut için aktif sonraki komutlarda pasif
unsigned int istasyon = 0;                                                // hangi istasyonun seçildiğini gösterir
unsigned int sendtoSlave = 0;                                             // pc den gelene dataları aldıktan sonra istasyonlara gönder
unsigned int sendtoPc = 0;                                                // istasyondan gelen bilgiyi pc ye göndermek içiin

//----------------------------- DEMUX SET --------------------------------//
void demux() {
  switch(istasyon){
    case 0: digitalWrite(S3, LOW); digitalWrite(S2, LOW); digitalWrite(S1, LOW); digitalWrite(S0, LOW); break;    // 0.istasyon
    case 1: digitalWrite(S3, LOW); digitalWrite(S2, LOW); digitalWrite(S1, LOW); digitalWrite(S0, HIGH); break;   // 1.istasyon
    case 2: digitalWrite(S3, LOW); digitalWrite(S2, LOW); digitalWrite(S1, HIGH); digitalWrite(S0, LOW); break;
    case 3: digitalWrite(S3, LOW); digitalWrite(S2, LOW); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH); break;
    case 4: digitalWrite(S3, LOW); digitalWrite(S2, HIGH); digitalWrite(S1, LOW); digitalWrite(S0, LOW); break;
    case 5: digitalWrite(S3, LOW); digitalWrite(S2, HIGH); digitalWrite(S1, LOW); digitalWrite(S0, HIGH); break;
    case 6: digitalWrite(S3, LOW); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, LOW); break;
    case 7: digitalWrite(S3, LOW); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH); break;
    case 8: digitalWrite(S3, HIGH); digitalWrite(S2, LOW); digitalWrite(S1, LOW); digitalWrite(S0, LOW); break;
    case 9: digitalWrite(S3, HIGH); digitalWrite(S2, LOW); digitalWrite(S1, LOW); digitalWrite(S0, HIGH); break;
    case 10: digitalWrite(S3, HIGH); digitalWrite(S2, LOW); digitalWrite(S1, HIGH); digitalWrite(S0, LOW); break;
    case 11: digitalWrite(S3, HIGH); digitalWrite(S2, LOW); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH); break;
    case 12: digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, LOW); digitalWrite(S0, LOW); break;
    case 13: digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, LOW); digitalWrite(S0, HIGH); break;
    case 14: digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, LOW); break;
    case 15: digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH); break;
  }
  delay(3); // demux un ayar çekmesini bekle
}

void serialEvent()                                                        // serial0 kesmesi
{
  while (Serial.available()) {                                            // bilgisayardan data geldiğinde
    char inChar_pc = (char)Serial.read();
    inputString_pc += inChar_pc;
    
    if (inChar_pc == ' ') {
      if(select_active == 1){                                             // bir kere istasyon bilgisini oku
        select_active = 0;
        istasyon = inputString_pc.toInt();                                // istasyon bilgisini oku
        inputString_pc = "";                                              // istasyon bilgisi reçete bilgisinden ayırmak için sıfırla
        demux();                                                          // demux u ayarla
      }
    }
    
    switch(inChar_pc) {                                                   // manuel komutlar geldiğinde
      case 'd':                                                           // reçete bilgilerini gönder
        select_active = 1;                                                // tekrar reçete göndermek için 1 lenmesi gerekir                                         
        mySerial.print(inputString_pc);                                   // istasyona bilgileri gönder (mySerial.print())
        mySerial.flush();                                                 // datanın gönderilmesini bekle
        inputString_pc = "";                                              // yeni bilgiler için stringi boşalt
        break;
      case 's':                                                           // test başlat komutu
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
      case 'r':                                                           // test reset komutu
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
      case 'p':                                                           // test pause komutu
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
      case 'u':                                                           // test güncelle komutu
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
      case 'f':                                                           // test durmuş posizyondayken servise hava ver komutu
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
      case 'j':                                                           // test durmuş posizyondayken imdat hava ver komutu
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
      case 'k':                                                           // manuel kaçak servis testini yap
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
      case 'n':                                                           // manuel kaçak imdat testini yap
        select_active = 1;
        mySerial.print(inputString_pc);
        inputString_pc = "";
        break;
    }
  }
}


//---------------------- CONFİGURASYON AYARLARI --------------------------//
void setup(){
  
  Serial.begin(19200);                                                    // Open serial communications and wait for port to open: 
  delay(1000);
  inputString_pc.reserve(256);                                            // bellekte 256 byte rezerve et
  inputString_istasyon.reserve(256);
  mySerial.begin(19200);                                                  // set the data rate for the SoftwareSerial port
  delay(1000);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
 
}

//------------------------------------------------------------------------//
//-------------------------- ANA PROGRAM ---------------------------------//
void loop() {
  delay(20);        // gecikme yapılmaz ise pc ye data göndermede hata oluşabiliyor

  while (mySerial.available()) {                                          // istasyonlardan data geldiğinde
    char inChar_istasyon = (char)mySerial.read(); 
    inputString_istasyon += inChar_istasyon;
    sendtoPc = 1;                                                         // istasyondan bilgi geldiğinde 1 le
  }
  delay(5);
  
  if(sendtoPc == 1){                                                      // istasyondan gelen bilgiyi pc ye bir kere gönder
    sendtoPc = 0;
    Serial.println(inputString_istasyon);     // sıkıntı println komutunda neden print değil
    Serial.flush();
    inputString_istasyon = "";
  }
  
}


