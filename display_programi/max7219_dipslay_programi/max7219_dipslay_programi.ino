/*
prg adı: max7219_display_programi
board: arduino nano
yazan: REMZİ ŞAHİNOĞLU
tarih: 13.04.2016

bu program max7219 entegresini kullanarak 8 adet 7-segmentli displayi sürer
iki anahtar vardır birisi reed switch diğeri datayı resetler ve her çevrimde
eeprom belleğe data kaydedilir. bu sayede enerji kesilse bile bilgi kaybolmaz
körüğün full ve sıfır stroğuna sensor bağlanmalıdır ikisi yazılımda ve kapısı
ile bağlanmıştır. 

*/
#include <EEPROM.h>
#include "LedControl.h"
// Arduino Pin 10 to DIN, 11 to LOAD/CS, 12 to Clk, no.of devices is 1
LedControl lc = LedControl(10,12,11,1);

// Arduino Pin 7 to DIN, 5 to LOAD/CS, 6 to Clk, no.of devices is 1
//LedControl lc = LedControl(7,6,5,1);

//---------------------------- DEĞİŞKENLER -------------------------------//
const int reed_switch_full = 4;
const int reed_switch_zero = 3;
const int reset_switch = 2;
int switch_code = 1;
int zero = 0;
signed long cevrim = 0;

char ekran[8] = {};                                                       // 8 display
int index = 0;

//--------------------------- EEPROM WRİTE -------------------------------//
void ee_write_long(unsigned int addr , signed long *longptr)
{
unsigned char edata;
unsigned char I;
    for(I=0;I<4;I++){
      edata = *((unsigned char *)longptr+I);
      EEPROM.write(addr+I,edata);
   }
}

//---------------------------- EEPROM READ -------------------------------//
void ee_read_long(unsigned int addr , signed long *longptr)
{
unsigned char edata;
unsigned char I;
   for(I=0;I<4;I++){
      edata=EEPROM.read(I+addr);   
        *((unsigned char *)longptr+I) = edata;
   }
}

//--------------------------- EKRANI AYARLA ------------------------------//
void ekran_ayarla()
{   
  index = 0;
  for (int i = 0; i < String(cevrim).length(); i++)
  {
    char inChar = (char)String(cevrim)[i];                                // tek bir byte oku
    switch(index)
    {
      case 0:                 // 1.karakter okunduğunda
        ekran[7] = ' ';       // değer yoksa display boş gözüksün
        ekran[6] = ' ';       // değer yoksa display boş gözüksün
        ekran[5] = ' ';       // değer yoksa display boş gözüksün
        ekran[4] = ' ';       // değer yoksa display boş gözüksün
        ekran[3] = ' ';       // değer yoksa display boş gözüksün
        ekran[2] = ' ';       // değer yoksa display boş gözüksün
        ekran[1] = ' ';       // değer yoksa display boş gözüksün
        ekran[0] = inChar;
        break;
        
      case 1:                 // 2.karakter okunduğunda
        ekran[7] = ' ';       // değer yoksa display boş gözüksün
        ekran[6] = ' ';       // değer yoksa display boş gözüksün
        ekran[5] = ' ';       // değer yoksa display boş gözüksün
        ekran[4] = ' ';       // değer yoksa display boş gözüksün
        ekran[3] = ' ';       // değer yoksa display boş gözüksün
        ekran[2] = ' ';       // değer yoksa display boş gözüksün
        ekran[1] = ekran[0];  // 1.okunan katakteri 2.displaye kaydır
        ekran[0] = inChar;
        break;
        
      case 2:                 // 3.karakter okunduğunda
        ekran[7] = ' ';       // değer yoksa display boş gözüksün
        ekran[6] = ' ';       // değer yoksa display boş gözüksün
        ekran[5] = ' ';       // değer yoksa display boş gözüksün
        ekran[4] = ' ';       // değer yoksa display boş gözüksün
        ekran[3] = ' ';       // değer yoksa display boş gözüksün
        ekran[2] = ekran[1];  // 1.okunan katakteri 3.displaye kaydır
        ekran[1] = ekran[0];  // 2.okunan katakteri 2.displaye kaydır
        ekran[0] = inChar;
        break;
        
      case 3:                 // 4.karakter okunduğunda
        ekran[7] = ' ';       // değer yoksa display boş gözüksün
        ekran[6] = ' ';       // değer yoksa display boş gözüksün
        ekran[5] = ' ';       // değer yoksa display boş gözüksün
        ekran[4] = ' ';       // değer yoksa display boş gözüksün
        ekran[3] = ekran[2];  // 1.okunan katakteri 4.displaye kaydır
        ekran[2] = ekran[1];  // 2.okunan katakteri 3.displaye kaydır
        ekran[1] = ekran[0];  // 3.okunan katakteri 2.displaye kaydır
        ekran[0] = inChar;
        break;
        
      case 4:                 // 5.karakter okunduğunda
        ekran[7] = ' ';       // değer yoksa display boş gözüksün
        ekran[6] = ' ';       // değer yoksa display boş gözüksün
        ekran[5] = ' ';       // değer yoksa display boş gözüksün
        ekran[4] = ekran[3];  // 1.okunan katakteri 4.displaye kaydır
        ekran[3] = ekran[2];  // 2.okunan katakteri 3.displaye kaydır
        ekran[2] = ekran[1];  // 3.okunan katakteri 2.displaye kaydır
        ekran[1] = ekran[0];  // 4.okunan katakteri 1.displaye kaydır
        ekran[0] = inChar;
        break;
        
      case 5:                 // 6.karakter okunduğunda
        ekran[7] = ' ';       // değer yoksa display boş gözüksün
        ekran[6] = ' ';       // değer yoksa display boş gözüksün
        ekran[5] = ekran[4];  // 1.okunan katakteri 5.displaye kaydır
        ekran[4] = ekran[3];  // 2.okunan katakteri 4.displaye kaydır
        ekran[3] = ekran[2];  // 3.okunan katakteri 3.displaye kaydır
        ekran[2] = ekran[1];  // 4.okunan katakteri 2.displaye kaydır
        ekran[1] = ekran[0];  // 5.okunan katakteri 1.displaye kaydır
        ekran[0] = inChar;
        break;
        
      case 6:                 // 7.karakter okunduğunda
        ekran[7] = ' ';       // değer yoksa display boş gözüksün
        ekran[6] = ekran[5];  // 1.okunan katakteri 6.displaye kaydır
        ekran[5] = ekran[4];  // 2.okunan katakteri 5.displaye kaydır
        ekran[4] = ekran[3];  // 3.okunan katakteri 4.displaye kaydır
        ekran[3] = ekran[2];  // 4.okunan katakteri 3.displaye kaydır
        ekran[2] = ekran[1];  // 5.okunan katakteri 2.displaye kaydır
        ekran[1] = ekran[0];  // 6.okunan katakteri 1.displaye kaydır
        ekran[0] = inChar;
        break;
        
      case 7:                 // 8.karakter okunduğunda
        ekran[7] = ekran[6];  // 1.okunan katakteri 7.displaye kaydır
        ekran[6] = ekran[5];  // 2.okunan katakteri 6.displaye kaydır
        ekran[5] = ekran[4];  // 3.okunan katakteri 5.displaye kaydır
        ekran[4] = ekran[3];  // 4.okunan katakteri 4.displaye kaydır
        ekran[3] = ekran[2];  // 5.okunan katakteri 3.displaye kaydır
        ekran[2] = ekran[1];  // 6.okunan katakteri 2.displaye kaydır
        ekran[1] = ekran[0];  // 7.okunan katakteri 1.displaye kaydır
        ekran[0] = inChar;
        break;
    }
    index++;
  }
}

//--------------------------- KONFİGURASYON ------------------------------//
void setup()
{
  // Initialize the MAX7219 device
  lc.shutdown(0,false);                                                   // Enable display
  lc.setIntensity(0,8);                                                   // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);                                                     // Clear display register

  pinMode(reed_switch_full, INPUT_PULLUP);                                // reed switchin bağlandığı pin
  pinMode(reed_switch_zero, INPUT_PULLUP);                                // reed switchin bağlandığı pin
  pinMode(reset_switch, INPUT_PULLUP);                                    // datanın sıfırlanması için

  ee_read_long(0x00, &cevrim);                                            // epromdaki cycle değerini oku
  delay(100);
  ekran_ayarla();

  for (int i = 0; i < String(cevrim).length(); i++)                       // çevrim uzunluğu kadar döngü yap
  {
    lc.setDigit(0,i,(String(ekran[i])).toInt(),false);                    // (grup no, digit no, data, point) eğer true ise point yanar
  }
}

//---------------------------- ANA PROGRAM -------------------------------//
void loop()
{
  if(digitalRead(reset_switch) == 0 )                                     // DATA SIFIRLANMASI İSTENDİĞİNDE
  {
    cevrim = 0;
    ee_write_long(0x00, &cevrim);                                         // eepromu sıfırla
    ekran_ayarla();
    lc.clearDisplay(0);                                                   // digitlerin bufferını temizle
  }
  
  if(digitalRead(reed_switch_zero) == 0 )                                 // SENSORDEN DATA ALINDIĞINDA
  {
    zero = 1;   
  }
  
  if(zero == 1)
  {
    if(digitalRead(reed_switch_full) == 0 )                               // SENSORDEN DATA ALINDIĞINDA
    {
      zero = 0;
      switch_code = 1;   
    }
  }
  
  if( switch_code == 1 )
  {
    switch_code = 0;
    cevrim++;
    ee_write_long(0x00, &cevrim);                                         // cycle değerini eproma yaz
    ekran_ayarla();
    
    for (int i = 0; i < String(cevrim).length(); i++)                     // çevrim uzunluğu kadar döngü yap
    {
      lc.setDigit(0,i,(String(ekran[i])).toInt(),false);                  // (grup no, digit no, data, point) eğer true ise point yanar
    }
    delay(100);
  }
  delay(6);
}




