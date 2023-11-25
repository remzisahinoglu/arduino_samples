/*
pr.ad: cigdem_hediye
board: nano
tarih: 25.10.2015
yazan: remzi şahinoğlu

bu prgrama arduino nano için yazılış olup, dijital çıkışlara
bağlı olan ledler ile havada yazı yazdırmaya  yarar.  ledler
tek sutun olarak düzenlenmiştir. yazdırılacak yazı sutunlara
bölünerek sırasıyla baştan sona ledlere yansıtılır.  bu süre
çok kısa olduğundan yazının okunabilmesi  için elle  belirli
hızda tekrarlanan bir periyotta hareket ettirilmesi gerekir.

PIN I/O
D0 : RX
D1 : TX
D2 : kelime değiştirme anahtarı
D3 : boş
D4-D12 : Led (9 adet)
D13: boş

A0-A7 : boş
*/

// çigdem kelimesi için binary kod dizisi
int cigdem[9][37] = {{0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0},
                     {0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,1,1,0},
                     {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0},
                     {1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0},
                     {1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0},
                     {1,0,0,0,0,0,0,1,0,1,0,0,1,1,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
                     {1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
                     {0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
                     {0,0,1,1,0,0,0,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0}};
// remzi kelimesi için binary kod dizisi
int remzi[9][30] = {{1,1,1,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0},
                    {1,0,0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0},
                    {1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0},
                    {1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0},
                    {1,0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0},
                    {1,1,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0},
                    {1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0},
                    {1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0},
                    {1,0,0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0}};

int kelime_zamani = 500;                  // kelimeler arasındaki gecikme ms
int sutun_zamani = 10;                    // sutunlar arasındaki gecikme ms

void setup() {
  Serial.begin(9600);                     // seriport iletişimini başlat
  delay(1000);
  Serial.println("merhaba cigdem :)");
  
  for(int i = 4; i < 12; i++){
    pinMode(i, OUTPUT);                   // D4-D12 pinleri(9pin) çıkış olarak ayarlandı
  }  
  pinMode(2, INPUT);                      // D2 pini giriş olarak ayarlandı 
  for(int i = 4; i < 13; i++){
    digitalWrite(i, LOW);                 // D4-D13 pinleri(10pin) 0 yapıldı
  }
}

void loop() {
  delay(kelime_zamani);                   // kelimeler arasındaki gecikme
  
  if(digitalRead(2) == 1){                // D2 pinine bağlı anahtar basılı ise "çiğdem" yaz
    for(int b = 0; b < 37; b++){          // a satırları, b sutunları temsil eder
      for(int a = 4; a < 13; a++){        // ilk sutundan başlayarak sırasıyla gönder 
        digitalWrite(a, cigdem[a-4][b]);  // ledleri yakıp söndürmek için 
        //Serial.print(cigdem[a-4][b]);   // pc de debug için aktif et
      }
      delay(sutun_zamani);                // sutunlar arasındaki gecikme
      //Serial.println(" ");              // pc de debug için aktif et
    }
  }
  else{                                   // anahtar basılı değil ise "remzi" yaz
    for(int b = 0; b < 30; b++){          // a satırları, b sutunları temsil eder
      for(int a = 4; a < 13; a++){        // ilk sutundan başlayarak sırasıyla gönder
        digitalWrite(a, remzi[a-4][b]);   // ledleri yakıp söndürmek için 
        //Serial.print(remzi[a-4][b]);    // pc de debug için aktif et
      }
      delay(sutun_zamani);                // sutunlar arasındaki gecikme
      //Serial.println(" ");              // pc de debug için aktif et
    }
  }
  
  
}













