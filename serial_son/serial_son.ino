/*
bu program hücre(slave) arduino programıdır. master arduinodan gelen verilerin
ve dataların işletilmesinden sorumludur.

yazan: remzi şahinoğlu
tarih: 6.7.2015
*/


//---------------------------- DEĞİŞKENLER -------------------------------//
unsigned int test_start = 0;                                              // test bittiğinde 0 olur ve test durur, start komutu pc den gelir
unsigned int test_reset = 0;                                              // reset komutu geldiğinde 1 olur
unsigned int test_pause = 0;                                              // test pause yapılmak istendiğinde 1 olur, komut pc den gelir
unsigned int test_tamamlandi = 0;                                         // pc den gönderilen test bittiğinde 0 olur
unsigned int sensor_kontrol = 0;                                          // stroke sensörlerini devreye almak için
unsigned int basinc_kontrol = 0;                                          // her çevrimde basınç kontrol yapmak için 1 olur, komut pc den gelir
unsigned int guncelle = 0;                                                // pc den guncelle komutu geldiğinde 1 olur ve test durum bilgilerini gönderir
unsigned int hava_ver = 0;                                                // servise veya imdata manuel hava verme komutu
unsigned int servis_hava_ver = 0;                                         // servise hava verilme komutu geldiğinde 1 olur
unsigned int imdat_hava_ver = 0;                                          // imdata hava verilme komutu geldiğinde 1 olur
unsigned int faz = 0;                                                     // faz bilgisini tutar
unsigned int recete = 0;                                                  // recetenin gelip gelmediği bilgisini tutar
unsigned int ariza_aktif = 0;                                             // arıza olduğunda testi durdurması için 1 olur, komut pc den gelir

String bilgi = "";
String inputString = "";                                                  // reçete bilgileri bu stringe yazılır
unsigned int dataBlock = 0;                                               // data bloklarını ayırmak için sayıcı
boolean stringComplete = false;                                           // reçete stringi tamamlandığında true olur

//------------------------- PERİYOD ATAMALARI ----------------------------//
unsigned int servis_baslama_sn = 0;                                       // servise ilk havanın verilme saniyesi
unsigned int servis_doldurma_sn = 0;                                      // servise havanın verili durma süresi
unsigned int servis_bosaltma_sn = 0;                                      // serviseteki havanın boşaltma süresi

unsigned int imdat_baslama_sn = 0;
unsigned int imdat_doldurma_sn = 0;
unsigned int imdat_bosaltma_sn = 0;

//-------------------------- ÇEVRİM ATAMALARI ----------------------------//
unsigned long toplam_cevrim = 0;                                          // toplam çevrim sayısı
unsigned long baslama_cevrimi = 0;                                        // teste başlama çevrimi, normalde 0

unsigned int ic_dongu_1_kod = 0;                                          // 1 = döngünün aktif olduğunu, 0 = döngünün pasif olduğunu gösterir
unsigned int ic_dongu_2_kod = 0;

unsigned long ic_dongu_1 = 0;                                             // birinci adım iç çevrim adedi sayıcısı
unsigned long ic_hedef_dongu_1 = 0;                                       // yapması istenilen hedef çevrim adedi

unsigned long ic_dongu_2 = 0;                                             // ikinci adım iç çevrim adedi
unsigned long ic_hedef_dongu_2 = 0;                                       // yapması istenilen hedef çevrim adedi

unsigned long dis_dongu_1 = 0;                                            // dış döngü çevrim adedi sayıcısı
unsigned long dis_cevrim_hedef_1 = 0;                                     // yapması istenilen hedef çevrim adedi

//-------------------- BASINÇ DEĞERLERİ ATAMALARI ------------------------//
float input_oransal_s_1 = 0;                                              // ilk adım için servis basınç değeri (bar)
unsigned int output_oransal_servis_1 = 0;                                 // pwm sinyalinin çıkış değeri (0-255) 
float input_oransal_s_2 = 0;                                              // ikinci adım için servis basınç değeri (bar)
unsigned int output_oransal_servis_2 = 0;                                 // pwm sinyalinin çıkış değeri (0-255) 

float transmitter_max_bar = 10;                                           // servis/imdat basınç sensörünün max değerini basınç cinsinden(bar) olarak buraya girin
float transmitter_min_bar = 0;                                            // servis/imdat basınç sensörünün min değerini basınç cinsinden(bar) olarak buraya girin

//----------------------- KAÇAK TESTİ ATAMALARI --------------------------//
unsigned int kacak_servis_test_active = 0;                                // servis kaçak testini aktif etmek için
unsigned int kacak_imdat_test_active = 0;                                 // servis kaçak testini aktif etmek için

unsigned int kacak_var_servis = 0;                                        // kaçak olduğunda 1 olur
unsigned int kacak_var_imdat = 0;

unsigned int kacak_servis_start = 0;                                      // manuel olarak servis kaçağını başlatmak için
unsigned int kacak_imdat_start = 0;

unsigned long kacak_cevrim = 0;                                           // kaçak çevrim adedi sayıcısı
unsigned long kacak_hedef_cevrim = 0;                                     // yapması istenilen hedef çevrim adedi

float kacak_testi_bar = 0;                                                // kaçak testi servis basınç değeri (bar)
float kacak_kontrol_bar = 0.0;                                            // kaçak kontrol basınç aralığı (bar)

//---------------------- SERİ PORT KESMESİ -------------------------------//
void serialEvent()                                                        // seri iletişim kesmesi oluştuğunda
{
  while (Serial.available())                                              // bufferda okuacak veri olduğu sürece tek tek byte ları oku
  {
    char inChar = (char)Serial.read();                                    // tek bir byte oku
    inputString += inChar;                                                // string değişkenine ekle
    
    if (inChar == 'd')                                                    // şartname datası geldiğinde
    {  
      dataBlock = 0;
      for (int i = 0; i < inputString.length(); i++)
      {
        char ch = inputString[i];
        if (ch == ';')
        {
          dataBlock++;
          switch(dataBlock)
          {
             case 1: servis_baslama_sn = bilgi.toInt(); break;
             case 2: servis_doldurma_sn = bilgi.toInt(); break;
             case 3: servis_bosaltma_sn = bilgi.toInt(); break;
             case 4: imdat_baslama_sn = bilgi.toInt(); break;
             case 5: imdat_doldurma_sn = bilgi.toInt(); break;
             case 6: imdat_bosaltma_sn = bilgi.toInt(); break;
             case 7: baslama_cevrimi = bilgi.toInt(); break;            // int türüne çevrildi fakat long değişkenine atandı çünkü int türü 32768 e kadar yüklenebilir fazlası için long olması gerek
             case 8: ic_dongu_1_kod = bilgi.toInt(); break;             // ilk adımın iç döngü kod değerini oku int türüne çevir ilgili değişkene ata           
             case 9: ic_dongu_2_kod = bilgi.toInt(); break;             // ikinci adımın iç döngü kod değeri
             case 10: dis_cevrim_hedef_1 = bilgi.toInt(); break;        // dış çevrim adedi
             case 11: ic_hedef_dongu_1 = bilgi.toInt(); break;          // ilk adımın iç çevrim adedi
             case 12: ic_hedef_dongu_2 = bilgi.toInt(); break;          // ikinci adımın iç çevrim adedi
             case 13: kacak_hedef_cevrim = bilgi.toInt(); break;        // kaçak testi "x" çevrimde bir yap         
             case 14: input_oransal_s_1 = bilgi.toFloat(); break;       // ilk adımın servis oransal valf basınç değeri
             case 15: input_oransal_s_2 = bilgi.toFloat(); break;       // ikinci adımın servis oransal valf basınç değeri
             case 16: kacak_testi_bar = bilgi.toFloat(); break;         // kaçak testi basınç değeri
             case 17: kacak_kontrol_bar = bilgi.toFloat(); break;       // kaçak testi kontrol basınç değeri
             case 18: kacak_servis_test_active = bilgi.toInt(); break;  // kaçak servis testi basınç değeri
             case 19: kacak_imdat_test_active = bilgi.toInt(); break;   // kaçak servis testi basınç değeri
             case 20: sensor_kontrol = bilgi.toInt(); break;            // sensor kontrol
             case 21: basinc_kontrol = bilgi.toInt(); break;            // basınc kontrol
             case 22: faz = bilgi.toInt(); break;                       // faz bilgisi
             case 23: ariza_aktif = bilgi.toInt(); break;               // arıza olduğunda testi durdur
          }
          bilgi = "";                                                   // yeni paket için temizle
        }
        else
        {
          bilgi += ch;                                                  // paketi oluştur
        }
      }
      
      dataBlock = 0;                                                    // yeni paket kümesi geldiğinde tekrardan sıfırdan başla
      inputString = "";                                                 // kümenin hafızasını temizle
      
  
      Serial.println(String(servis_baslama_sn) + ";" + String(servis_doldurma_sn) + ";" + String(servis_bosaltma_sn));
      Serial.println(String(imdat_baslama_sn) + ";" + String(imdat_doldurma_sn) + ";" + String(imdat_bosaltma_sn));
               
      Serial.println(baslama_cevrimi);
      Serial.println(ic_dongu_1_kod);
      Serial.println(ic_dongu_2_kod);
      Serial.println(dis_cevrim_hedef_1);
      Serial.println(ic_hedef_dongu_1);
      Serial.println(ic_hedef_dongu_2);
      Serial.println(kacak_hedef_cevrim);
             
      Serial.println(input_oransal_s_1);
      Serial.println(input_oransal_s_2);
      Serial.println(kacak_testi_bar);
      Serial.println(kacak_kontrol_bar);
               
      Serial.println(kacak_servis_test_active);
      Serial.println(kacak_imdat_test_active);
      Serial.println(sensor_kontrol);
      Serial.println(basinc_kontrol);
               
      Serial.println(faz);
      Serial.println(ariza_aktif);
     
    }
    
    
    
    // ** buraya komutların harflerinizi yaz ** //
    // ** anaprogramda resset veya pause için bitleri kontrol ettir ** //
  }
}


//---------------------- BAŞLANGIÇ AYARLARI ------------------------------//
void setup() 
{
   Serial.begin(19200);                                                   // initialize serial: 19200 bit per second
   delay(1000);

   
}



//------------------------------------------------------------------------//
//-------------------------- ANA PROGRAM ---------------------------------//
//------------------------------------------------------------------------//
void loop() 
{
  delay(5);
  
  
  

}







