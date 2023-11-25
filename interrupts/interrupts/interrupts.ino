/*
yazan: Remzi Şahinoğlu
tarih: 09.03.2016
board: arduino uno

kesme algoritması için yazılmıştır

*/

int pin = 13;
volatile int state = LOW;

void setup() {
    pinMode(pin, OUTPUT);
    attachInterrupt(0, blink, FALLING);
}

void loop() {
    digitalWrite(pin, state);
    delay(100);
}

void blink() {
    state = !state;
    
}
