// kaçak testi algoritması
// tarih: 17.6.2015
// yazan: Remzi Şahinoğlu

// bu program ömür test sistemleri kontrolü otomasyonunda kullanılacak
// kaçak testi algoritmasını yürütür.

//***************************** ÇIKIŞLAR *****************************//
// selenoid valfler çıkışları  (digital çıkış)
const int servis_valf = 6;
const int imdat_valf = 7;
const int servis_kilit = 8;
const int imdat_kilit = 9;
// oransal valf çıkışları (pwm çıkış)
const int oransal_s = 5;
const int oransal_i = 3;  // devrede eklenmekten vazgeçildi sadece servis kontrolü var.

//******** çıkışları terslemek için ********//
// 4'lü röle kartının ters balantısından dolayı 
// eğer ters tetiklenen bir kart gelirse 
int tersle = 1;  // arduino çıkışına 0(LOW) verdiğimizde selonoid valf enerjilernir röle kartı ters tetikleme olduğundan dolayı
int duzle = 0;   // arduino çıkışına 1(HIGH) verdiğimizde selonoid valf pasiflenir.

//***************************** GİRİŞLER *****************************//
// transmiter girişleri  (analog giriş)
const int servis_bar = 0;  // A0
const int imdat_bar = 1;   // A1
// sensör girişleri  (digital giriş)
const int full_stroke = 0;  
const int zero_stroke = 1;
const int acil_buton = 2;


//**************************** DEĞİŞKENLER ***************************//
//******* pc den gelen reçete değerleri ******//




int t = 0;  // zaman for döngüsü için
int i = 1;  // periyod adımlarını arttırmak için atandı
int periyod_uzunlugu_1 = 0;
int periyod_uzunlugu_2 = 0;
int x = 0;  // periyod uzunluğu hesaplama için
//******* periyoddaki zaman aralığı değeri *******//
int interval = 1000;  // milisaniye
//******* test bittiğinde ************************//
int test_durumu = 1;  // test bittiğinde 0 ve olur test durur
//******* toplam çevrim sayısı *******************//
long toplam_cevrim = 0;

// 10sn periyod için zaman aralığı 1sn olacak şekilde servis ve imdat valflerini aç-kapa yapma algoritması
// 3 farklı dizi ve 1 adet zaman adımı değişkeni sayesinde istediğimiz algoritmayı oluşturabiliriz.
//                       sn:  1 2 3 4 5 6 7 8 9*0 1 2 3 4 5 6 7 8 9 20
const int periyod_1[20]     ={1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   // periyod[5]={1,2,3,4,5}  // 1 = periyod[0],  5 = periyod[4] oluyor
const int servis_check_1[20]={1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const int imdat_check_1[20] ={0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

const int periyod_2[20]     ={1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   // periyod[5]={1,2,3,4,5}  // 1 = periyod[0],  5 = periyod[4] oluyor
const int servis_check_2[20]={1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const int imdat_check_2[20] ={1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//**** iç ve dış döngü kodları atamaları *********//
// 1= döngünün aktif olduğunu, 0= döngünün pasif olduğunu gösterir
const int dis_dongu_1_kod = 1;
const int ic_dongu_1_kod = 1;
const int ic_dongu_2_kod = 1;

//*********** çevrim sayısı atamaları ************//
// döngü'ler ilk başta sıfır her çalışmada içindeki değeri +1 arttırır
// hedef_döngü'ler ise çalışması istenilen çevrims sayısını saklarlar
// toplam çevrim = (ic_hedef_dongu_1 + ic_hedef_dongu_2) * dis_hedef_dongu_1    olarak hesaplanabilir
//**** iç çevrimler ****//
unsigned long ic_dongu_1 = 0;          // birinci adım çevrim adedi
unsigned long ic_hedef_dongu_1 = 3;

unsigned long ic_dongu_2 = 0;          // ikinci adım çevrim adedi
unsigned long ic_hedef_dongu_2 = 4;

//**** dış çevrimler ****//
unsigned long dis_dongu_1 = 0;         // dış döngü çevrim adedi
unsigned long dis_hedef_dongu_1 = 2;

//******* servis oransal valfinin max ve min atamaları ******//
float input_oransal_s_1 = 8;  // giriş sinyalinin "bar" cinsinden değeri min max arasında olması gerekir ondalıklı sayı girilebilmesi için float olarak atandı
int output_oransal_servis_1 = 0;  // pwm sinyalinin çıkış değeri (0-255) 

float input_oransal_s_2 = 6;  // giriş sinyalinin "bar" cinsinden değeri min max arasında olması gerekir ondalıklı sayı girilebilmesi için float olarak atandı
int output_oransal_servis_2 = 0;  // pwm sinyalinin çıkış değeri (0-255) 

const int servis_max_bar = 10;  // basınç sensörünün max değerini basınç cinsinden(bar) olarak buraya girin
const int servis_min_bar = 0;  // basınç sensörünün min değerini basınç cinsinden(bar) olarak buraya girin

//******* imdat oransal valfinin max ve min atamaları ******//  (imdat kısmı içi orsansalden vazgeçildi)

float input_oransal_i_1 = 8;  // giriş sinyalinin "bar" cinsinden değeri min max arasında olması gerekir
int output_oransal_imdat_1 = 0;  // pwm sinyalinin çıkış değeri (0-255) 

float input_oransal_i_2 = 8;  // giriş sinyalinin "bar" cinsinden değeri min max arasında olması gerekir
int output_oransal_imdat_2 = 0;  // pwm sinyalinin çıkış değeri (0-255)

const int imdat_max_bar = 10;  // basınç sensörünün max değerini basınç cinsinden(bar) olarak buraya girin
const int imdat_min_bar = 0;  // basınç sensörünün min değerini basınç cinsinden(bar) olarak buraya girin

//******* kaçak testi atamaları
long kacak_cevrim = 0;
long kacak_cevrim_hedef = 5;

float imdat_testi_basinc = 8;
float servis_testi_basinc = 8;
float imdat_kontrol_degeri_1 = 2.0;  // bu değerin karşılığı 0->1024 analog data 0->10 bar interpolasyonundan 2 bar karşılığıdır
float imdat_kontrol_degeri_2 = 0.5;   // bu değerin ise 0.5 bar karşılığıdır

int y = 0;

float p0=0;
float p1_read[5]={};
float p1_ort = 0;
float p1 = 0;

float p2_read[5]={};
float p2_ort = 0;
float p2 = 0;

//********************* servis/imdat basınç değerlerini ayarlama ilk adım için ******************//
void basinci_ayarla_1(){
  output_oransal_servis_1 = 255 * (input_oransal_s_1 - servis_min_bar) / (servis_max_bar - servis_min_bar);    // interpolasyon
  analogWrite(oransal_s, output_oransal_servis_1);      // servis basıncını ayarla
  
  output_oransal_imdat_1 = 255 * (input_oransal_i_1 - imdat_min_bar) / (imdat_max_bar - imdat_min_bar);    // interpolasyon
  analogWrite(oransal_i, output_oransal_imdat_1);      // imdat basıncını ayarla
  
  //debug için yazıldı
  Serial.print(input_oransal_s_1);
  Serial.println(" bar ayarlandi");
  
  Serial.print(input_oransal_i_1);
  Serial.println(" bar ayarlandi");
  
  delay(1000);  // orsansal valfin basıncı ayarlaması için biraz bekle
}

//********************** test bittiğinde bütün çıkışları sıfırla ************************//
void test_bitti(){
  analogWrite(oransal_s, 0);
  analogWrite(oransal_i, 0);
  
  delay(500);
  
  digitalWrite(servis_valf, tersle);
  digitalWrite(imdat_valf, tersle);
  digitalWrite(servis_kilit, tersle);
  digitalWrite(imdat_kilit, duzle);
}

void bekle(int time){
  for(t = 1; t <= time; t++){
    delay(1000);
  }
}


void setup() {
  // bu döngü bir kez çalışır, config ayarları burada yapılır
  
  // ethernet udp protokolünü başlat
  
  Serial.begin(19200);  // rs232 yi başlat, çalışma hızı 9600 bit per second
  pinMode(full_stroke, INPUT);
  pinMode(zero_stroke, INPUT);
  pinMode(acil_buton, INPUT);
  pinMode(oransal_s, OUTPUT);
  //pinMode(oransal_i, OUTPUT);    // imdat için oransal valf kullanılmasından vazgeçildi
  pinMode(servis_valf, OUTPUT);
  pinMode(imdat_valf, OUTPUT);
  pinMode(servis_kilit, OUTPUT);
  pinMode(imdat_kilit, OUTPUT);
  
  // çıkışları sıfırla
  digitalWrite(servis_valf, tersle);
  digitalWrite(imdat_valf, tersle);
  digitalWrite(servis_kilit, tersle);
  digitalWrite(imdat_kilit, duzle);
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// ANA PROGRAM /////////////////////////////////////////
void loop() {
  delay(1000);
  
  if(test_durumu == 1){
    
    digitalWrite(imdat_kilit, duzle);
    input_oransal_i_1 = imdat_testi_basinc;
    basinci_ayarla_1();                                               // basıncı ayarla
    digitalWrite(imdat_valf, duzle);                                  // imdata hava verildi
    Serial.println("imdata hava verildi, 30sn bekliyor...");
    bekle(30);                                                        // 30 sn bekle stabilizasyon için
    digitalWrite(imdat_kilit, tersle);                                // havayı kitle
    p0 = analogRead(imdat_bar);                                       // ilk basınc değerini oku
    p0 = (p0 * 10) / 1024;                                            // bara çevrildi
    Serial.println(p0);
    Serial.println("imdatta hava kitlendi, 29sn bekliyor...");
    bekle(29);
    
    for(y = 0; y < 5; y++){
      p1_read[y] = analogRead(imdat_bar);                             // transmitteri oku 5 kez
      p1_ort = p1_read[y] + p1_ort;
      delay(200);
    }
    p1_ort = p1_ort / 5;                                              // 1 sn de 5 okuma yapıldı ve ortalaması alındı
    p1 = (p1_ort * 10) / 1024;                                        // bar cinsinden göstermek için yapıldı interpolasyon
    Serial.print("p1 bar cinsinden ort degeri: "); 
    Serial.println(p1);
  
    if(abs(p0 - p1) >= imdat_kontrol_degeri_1){
      Serial.println("imdat kacagi cok");
    }
    else{
      Serial.println("29sn bekliyor...");
      bekle(29);
      for(y = 0; y < 5; y++){
        p2_read[y] = analogRead(imdat_bar);                             // transmitteri oku 5 kez
        p2_ort = p2_read[y] + p2_ort;
        delay(200);
      }
      p2_ort = p2_ort / 5;                                              // 1 sn de 5 okuma yapıldı ve ortalaması alındı
      p2 = (p2_ort * 10) / 1024;                                        // bar cinsinden göstermek için yapıldı interpolasyon
      Serial.print("p2 bar cinsinden ort degeri: "); 
      Serial.println(p2); 
      
      if(abs(p2 - p1) >= imdat_kontrol_degeri_2){
        Serial.println("imdat kacagi az");
      }
    }
    Serial.println("kacak yok");
    Serial.println("test bitti");
    test_durumu = 0;
    test_bitti();
  }
  

}
















