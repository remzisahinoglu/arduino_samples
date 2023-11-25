#include <Keyboard.h>

void setup() {
  Keyboard.begin();
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(4) == 0){
    Keyboard.print("Qa2015!gear");
    delay(100);
    Keyboard.write(KEY_RETURN);
    delay(100);
    Keyboard.releaseAll();
  }
  delay(100);
}

