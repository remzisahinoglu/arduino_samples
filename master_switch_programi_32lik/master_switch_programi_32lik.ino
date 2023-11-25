/*
prg adı: master_switch_programi
board: arduino mega
tarih: 30.12.2015
yazan: Remzi ŞAHİNOĞLU

bu program pc den gelen reçete bilgilerinin, manuel komutların ve test
durum bilgilerinin pcden istasyonlara,istasyonlardan pcye aktarılmasnı
sağlar. her komutun başındaki ilk byte istasyon bilgisini temsil eder.
istasyon bilgisi okunduktan sonra demux ayarlanır.  reçete veya manuel
bilgiler ondan sonra okunduğu gibi yollanır.istasyondan gelen bilginin 
ilk byteı ise yine istasyon bilgisini temsil eder. bu bilgi diğer test
durum bilgileriyle birlikte pcye gönderilir. pc deki  arayüz tarafında
bu bilgi ayırt edilerek istenilen istasyon databaseinde saklanır.

pc nin seriport com1 inden arduinonun RX2'sine data girer. TX1' den ise
istasyonlara gönderilir.
*/

//------------------------------ ÇIKIŞLAR --------------------------------//
const int S0 = 8;                                                         // U1-TX'in A0(10.pin) demux en düşük biti
const int S1 = 9;                                                         // U1-TX'in A1(11.pin)
const int S2 = 10;                                                        // U1-TX'in A2(14.pin)
const int S3 = 11;                                                        // U1-TX'in A3(13.pin) demux en yüksek biti
const int S4 = 4;                                                         // U1-T0'ın A0(10.pin) demux en düşük biti
const int S5 = 5;                                                         // U1-T0'ın A1(11.pin)
const int S6 = 6;                                                         // U1-T0'ın A2(12.pin)
const int S7 = 7;                                                         // U1-T0'ın A3(13.pin) demux en yüksek biti

//---------------------------- DEĞİŞKENLER -------------------------------//
String inputString_pc = "";                                               // pc den gelen dataların tutulduğu string
String inputString_istasyon = "";                                         // istasyonlardan gelen dataların tutulduğu string

unsigned int select_active = 1;                                           // pc den gelen ilk komut için aktif sonraki komutlarda pasif, ilk olarak 1 olmalıdır
unsigned int istasyon = 0;                                                // hangi istasyonun seçildiğini gösterir
unsigned int sendtoPc = 0;                                                // istasyondan gelen bilgiyi pc ye göndermek içiin
unsigned int sendtoIstasyon = 0;                                          // pc den gelen bilgileri istasyonlara gönder

//----------------------------- DEMUX SET --------------------------------//
void demux() 
{
  switch(istasyon)
  {
    case 0:    // 0.istasyon
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;   // S7=0, S6=0, S5=0, S4=0 >>> 0-15 arasında
    case 1:    // 1.istasyon
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 2: 
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 3: 
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, HIGH); 
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 4: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 5: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 6: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 7: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 8: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 9: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 10: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 11: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 12: 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 13: 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 14: 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;
    case 15: 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, LOW); break;    
    case 16:    // 16.istasyon
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;   // S7=0, S6=0, S5=1, S4=0 >>> 16-31 arasında
    case 17:    // 17.istasyon
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 18: 
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 19: 
      digitalWrite(S3, LOW);  digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, HIGH); 
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, HIGH); digitalWrite(S4, LOW); break;
    case 20: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 21: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 22: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 23: 
      digitalWrite(S3, LOW);  digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 24: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 25: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 26: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 27: 
      digitalWrite(S3, HIGH); digitalWrite(S2, LOW);  digitalWrite(S1, HIGH); digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 28: 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 29: 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, LOW);  digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 30: 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, LOW);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
    case 31:    // 31.istasyon 
      digitalWrite(S3, HIGH); digitalWrite(S2, HIGH); digitalWrite(S1, HIGH); digitalWrite(S0, HIGH);
      digitalWrite(S7, LOW);  digitalWrite(S6, LOW);  digitalWrite(S5, LOW);  digitalWrite(S4, HIGH); break;
  }
  delay(3); // demux un ayar çekmesini bekle
}

//---------------------- SERIAL PORT 1 KESMESİ ---------------------------//
void serialEvent1()                                                       // serial1 kesmesi
{
  while (Serial1.available())                                             // istasyondan pc ye data gönder
  {
    char inChar_istasyon = (char)Serial1.read(); 
    inputString_istasyon += inChar_istasyon;
  }
  sendtoPc = 1;                                                           // istasyondan gelen datayı pc ye göndermek için 1 yap
}

//---------------------- SERIAL PORT 2 KESMESİ ---------------------------//
void serialEvent2()                                                       // serial0 kesmesi
{
  while (Serial2.available()) {                                           // bilgisayardan data geldiğinde
    char inChar_pc = (char)Serial2.read();
    inputString_pc += inChar_pc;
    
    if (inChar_pc == ' ') {                                               // gelen datanın ilk istasyon bilgisini ayır
      if(select_active == 1){                                             // bir kere istasyon bilgisini oku
        select_active = 0;
        istasyon = inputString_pc.toInt();                                // istasyon bilgisini oku
        inputString_pc = "";                                              // istasyon bilgisi reçete bilgisinden ayırmak için sıfırla
        demux();                                                          // demux u ayarla
      }
    }
  }
  select_active = 1;                                                      // demux u her kodda ayarlaması için 1le
  sendtoIstasyon = 1;
}

//---------------------- CONFİGURASYON AYARLARI --------------------------//
void setup()
{
  //Serial.begin(19200);                                                    // 19200 bps te seriportu-0 başlat
  //delay(1000);
  Serial1.begin(19200);                                                   // 19200 bps te seriportu-1 başlat
  delay(1000);
  Serial2.begin(19200);                                                   // 19200 bps te seriportu-2 başlat
  delay(1000);
  
  inputString_pc.reserve(256);                                            // bellekte 256 byte rezerve et
  inputString_istasyon.reserve(256);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
  pinMode(S6, OUTPUT);
  pinMode(S7, OUTPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  digitalWrite(S4, LOW);
  digitalWrite(S5, LOW);
  digitalWrite(S6, LOW);
  digitalWrite(S7, LOW);
}

//------------------------------------------------------------------------//
//-------------------------- ANA PROGRAM ---------------------------------//
void loop() 
{
  delay(6);                                                               // gecikme yapılmaz ise pc ye data göndermede hata oluşabiliyor
  
  if(sendtoPc == 1)                                                       // istasyondan gelen bilgiyi pc ye bir kere gönder
  {   
    sendtoPc = 0;                                                         // sürekli göndermemek için sıfırlandı
    Serial2.println(inputString_istasyon);                                // println komutunda neden print değil bilmiyorum ama çalışıyor
    Serial2.flush();
    inputString_istasyon = "";
  }
  
  if(sendtoIstasyon == 1)                                                 // pc den gelen dataları istasyondan gönder
  {
    sendtoIstasyon = 0;                                                   // sürekli göndermemek için sıfırlandı
    Serial1.print(inputString_pc);                                        // istasyona gönder
    Serial1.flush();
    inputString_pc = "";
  }
  
}


