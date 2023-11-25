const int led = 3;
const int pot = 0;
int deger = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  deger = analogRead(pot)/4;
  analogWrite(led, deger);
  delay(30);
  
}
