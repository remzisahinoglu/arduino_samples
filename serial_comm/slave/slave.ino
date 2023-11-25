/*
bu program hücre(slave) arduino programıdır. master arduinodan gelen verilerin
ve dataların işletilmesinden sorumludur.

yazan: remzi şahinoğlu
tarih: 6.7.2015
*/


//---------------------------- DEĞİŞKENLER -------------------------------//
String inputString = "";                                                  // reçete bilgileri bu stringe yazılır
unsigned int dataBlock = 0;                                               // data bloklarını ayırmak için sayıcı
boolean stringComplete = false;                                           // reçete stringi tamamlandığında true olur

unsigned int periyod_1[20] = {};                                          // periyodun birinci zamanı
unsigned int servis_check_1[20] = {};                                     // servisin birinci zamanı
unsigned int imdat_check_1[20] = {};                                      // imdatın birinci zamanı

unsigned int in_outer_cycle_code = 0;                                     // dış döngü kodu 
unsigned int in_inner_cycle_code = 0;                                     // iç döngü kodu
unsigned long in_outer_cycle = 0;                                         // dış döngü çevrim adedi
unsigned long in_inner_cycle = 0;                                         // iç döngü çevrim adedi
unsigned long in_leak_cycle = 0;                                          // kaçak çevrim adedi x çevrimde bir yap
float in_servis_bar = 0;                                                  // servis bar
float in_imdat_bar = 0;                                                   // imdat bar
float in_leak_test_bar = 0;                                               // kaçak testi bar
float in_leak_control_bar = 0;                                            // kaçak kontrol bar
unsigned int in_sensor_control = 0;                                       // sensor kontrol
unsigned int debug = 0;                                                   // telefon ile debug yapmak için 1:aktif, 0:pasif
// yeni değişkenleri buradan ekle


//---------------------- BAŞLANGIÇ AYARLARI ------------------------------//
void setup() {
   Serial.begin(9600);                                                    // initialize serial: 9600 bit per second
   delay(500);
   //Serial.println(SERIAL_RX_BUFFER_SIZE);                               // hardwareSerial.h dosyasında max 256 byte olarak ayarlandı
   inputString.reserve(200);                                              // reserve 200 bytes for the inputString:
   
   pinMode(6,OUTPUT);
   pinMode(7,OUTPUT);
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   
   digitalWrite(6, HIGH);
   digitalWrite(7, HIGH);
   digitalWrite(8, HIGH);
   digitalWrite(9, HIGH);
}

//---------------------- SERİ PORT KESMESİ -------------------------------//
void serialEvent() {                                                      // seri iletişim kesmesi oluştuğunda
   while (Serial.available()) {                                           // bufferda okuacak veri olduğu sürece tek tek byte ları oku
     char inChar = (char)Serial.read();                                   // tek bir byte oku
     inputString += inChar;                                               // string değişkenine ekle

     if (inChar == ' ') {                                                 // data bloğunun aralarına boşluk konularak veri gelecek
       dataBlock++;                                                       // data bloğundaki adımları seçmek için arttır
       switch(dataBlock){                                                 // data bloklarını sırasıyla oku     
         // periyod zaman çizelgesi bilgisini oku
         case 1: periyod_1[0] = inputString.toInt(); inputString = ""; break;
         case 2: periyod_1[1] = inputString.toInt(); inputString = ""; break;
         case 3: periyod_1[2] = inputString.toInt(); inputString = ""; break;
         case 4: periyod_1[3] = inputString.toInt(); inputString = ""; break;
         case 5: periyod_1[4] = inputString.toInt(); inputString = ""; break;
         case 6: periyod_1[5] = inputString.toInt(); inputString = ""; break;
         case 7: periyod_1[6] = inputString.toInt(); inputString = ""; break;
         case 8: periyod_1[7] = inputString.toInt(); inputString = ""; break;
         case 9: periyod_1[8] = inputString.toInt(); inputString = ""; break;
         case 10: periyod_1[9] = inputString.toInt(); inputString = ""; break;
         case 11: periyod_1[10] = inputString.toInt(); inputString = ""; break;
         case 12: periyod_1[11] = inputString.toInt(); inputString = ""; break;
         case 13: periyod_1[12] = inputString.toInt(); inputString = ""; break;
         case 14: periyod_1[13] = inputString.toInt(); inputString = ""; break;
         case 15: periyod_1[14] = inputString.toInt(); inputString = ""; break;
         case 16: periyod_1[15] = inputString.toInt(); inputString = ""; break;
         case 17: periyod_1[16] = inputString.toInt(); inputString = ""; break;
         case 18: periyod_1[17] = inputString.toInt(); inputString = ""; break;
         case 19: periyod_1[18] = inputString.toInt(); inputString = ""; break;
         case 20: periyod_1[19] = inputString.toInt(); inputString = ""; break;
         // servis zaman çizelgesi bilgisini oku
         case 21: servis_check_1[0] = inputString.toInt(); inputString = ""; break;
         case 22: servis_check_1[1] = inputString.toInt(); inputString = ""; break;
         case 23: servis_check_1[2] = inputString.toInt(); inputString = ""; break;
         case 24: servis_check_1[3] = inputString.toInt(); inputString = ""; break;
         case 25: servis_check_1[4] = inputString.toInt(); inputString = ""; break;
         case 26: servis_check_1[5] = inputString.toInt(); inputString = ""; break;
         case 27: servis_check_1[6] = inputString.toInt(); inputString = ""; break;
         case 28: servis_check_1[7] = inputString.toInt(); inputString = ""; break;
         case 29: servis_check_1[8] = inputString.toInt(); inputString = ""; break;
         case 30: servis_check_1[9] = inputString.toInt(); inputString = ""; break;
         case 31: servis_check_1[10] = inputString.toInt(); inputString = ""; break;
         case 32: servis_check_1[11] = inputString.toInt(); inputString = ""; break;
         case 33: servis_check_1[12] = inputString.toInt(); inputString = ""; break;
         case 34: servis_check_1[13] = inputString.toInt(); inputString = ""; break;
         case 35: servis_check_1[14] = inputString.toInt(); inputString = ""; break;
         case 36: servis_check_1[15] = inputString.toInt(); inputString = ""; break;
         case 37: servis_check_1[16] = inputString.toInt(); inputString = ""; break;
         case 38: servis_check_1[17] = inputString.toInt(); inputString = ""; break;
         case 39: servis_check_1[18] = inputString.toInt(); inputString = ""; break;
         case 40: servis_check_1[19] = inputString.toInt(); inputString = ""; break;
         // imdat zaman çizelgesi bilgisini oku
         case 41: imdat_check_1[0] = inputString.toInt(); inputString = ""; break;
         case 42: imdat_check_1[1] = inputString.toInt(); inputString = ""; break;
         case 43: imdat_check_1[2] = inputString.toInt(); inputString = ""; break;
         case 44: imdat_check_1[3] = inputString.toInt(); inputString = ""; break;
         case 45: imdat_check_1[4] = inputString.toInt(); inputString = ""; break;
         case 46: imdat_check_1[5] = inputString.toInt(); inputString = ""; break;
         case 47: imdat_check_1[6] = inputString.toInt(); inputString = ""; break;
         case 48: imdat_check_1[7] = inputString.toInt(); inputString = ""; break;
         case 49: imdat_check_1[8] = inputString.toInt(); inputString = ""; break;
         case 50: imdat_check_1[9] = inputString.toInt(); inputString = ""; break;
         case 51: imdat_check_1[10] = inputString.toInt(); inputString = ""; break;
         case 52: imdat_check_1[11] = inputString.toInt(); inputString = ""; break;
         case 53: imdat_check_1[12] = inputString.toInt(); inputString = ""; break;
         case 54: imdat_check_1[13] = inputString.toInt(); inputString = ""; break;
         case 55: imdat_check_1[14] = inputString.toInt(); inputString = ""; break;
         case 56: imdat_check_1[15] = inputString.toInt(); inputString = ""; break;
         case 57: imdat_check_1[16] = inputString.toInt(); inputString = ""; break;
         case 58: imdat_check_1[17] = inputString.toInt(); inputString = ""; break;
         case 59: imdat_check_1[18] = inputString.toInt(); inputString = ""; break;
         case 60: imdat_check_1[19] = inputString.toInt(); inputString = ""; break;
         // çevrim periyod ve diğer bilgileri oku
         case 61: in_outer_cycle_code = inputString.toInt(); inputString = ""; break;    // ilk blok değerini oku int türüne çevir ve ata(dış döngü kodu)           
         case 62: in_inner_cycle_code = inputString.toInt(); inputString = ""; break;    // ikinci blok değerini oku int türüne çevir ve ata(iç döngü kodu)                      
         case 63: in_outer_cycle = inputString.toInt(); inputString = ""; break;         // int türüne çevrildi fakat long değişkenine atandı çünkü int türü 32768 e kadar yüklenebilir fazlası için long olması gerek                    
         case 64: in_inner_cycle = inputString.toInt(); inputString = ""; break;         // iç döngü adedi
         case 65: in_leak_cycle = inputString.toInt(); inputString = ""; break;          // dış döngü adedi
         case 66: in_servis_bar = inputString.toFloat(); inputString = ""; break;        // servis bar değeri: float türüne çevrildi çünkü bar değerleri ondalıklı sayı ve interpolasyon için gerekli                                            
         case 67: in_imdat_bar = inputString.toFloat(); inputString = ""; break;         // imdat bar değeri
         case 68: in_leak_test_bar = inputString.toFloat(); inputString = ""; break;     // kaçak testi bar değeri
         case 69: in_leak_control_bar = inputString.toFloat(); inputString = ""; break;  // kaçak testi kontrol bar değeri
         case 70: in_sensor_control = inputString.toInt(); inputString = ""; break;      // sernsor kontrol bilgisi
         case 71: debug = inputString.toInt(); inputString = ""; break;                  // debug
         //case 72: yeni komutlar buraya eklenebilir
       }
     }
     
     if (inChar == 'r') {                                                 // data bloğunun sonunda r harfi konulursa reçete alımı bitti demektir
       stringComplete = true;                                             // veri alımı bitti
       dataBlock = 0;                                                     // yeni data geldiğinde baştan okuma yapabilmek için sıfırla
     }
     
     if (inChar == 'a') {                                                 // yeni komuta burdan devam edebilirsin
       
     }
   }
}

//------------------------------------------------------------------------//
//-------------------------- ANA PROGRAM ---------------------------------//
//------------------------------------------------------------------------//
void loop() {
   delay(500);
   
   if (stringComplete) {                                                  // gelen datalar tamamlandığında
     Serial.println(in_outer_cycle_code);
     Serial.println(in_inner_cycle_code);
     Serial.println(in_outer_cycle);
     Serial.println(in_inner_cycle);
     Serial.println(in_leak_cycle);
     Serial.println(in_servis_bar);
     Serial.println(in_imdat_bar);
     Serial.println(in_leak_test_bar);
     Serial.println(in_leak_control_bar);
     Serial.println(in_sensor_control);
     Serial.println(periyod_1[19]);
     Serial.println(servis_check_1[19]);
     Serial.println(imdat_check_1[19]);
     
     inputString = "";                                                    // inputString in içeriğini temizle
     stringComplete = false;
   }


}
