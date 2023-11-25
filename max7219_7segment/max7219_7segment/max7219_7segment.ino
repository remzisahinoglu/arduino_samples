/*
prg adı: max7219_7segment
board: arduino nano
yazan: REMZİ ŞAHİNOĞLU
tarih: 13.04.2016

bu program max7219 entegresini kullanarak 8 adet 7-segmentli displayi sürer

*/

#include "LedControl.h"
// Arduino Pin 7 to DIN, 6 to Clk, 5 to LOAD/CS, no.of devices is 1
LedControl lc=LedControl(13,11,12,1);

void setup()
{
 // Initialize the MAX7219 device
  lc.shutdown(0,false);   // Enable display
  lc.setIntensity(0,10);  // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);     // Clear display register
}

void loop()
{
  lc.setDigit(0,3,1,true);    // (grup no, digit no, data, point) eğer true ise point yanar
  lc.setDigit(0,0,6,false);   //
  delay(1000);

  
}
