/*
prg adı: analog_read_write_shield_dual_test
tarih: 18.8.2015
yazan: Remzi ŞAHİNOĞLU

bu program istasyon arduinolarına bağlı olan dual analog shield modulunun 
test edilmesi için yazılmıştır

*/
String inputString = "";

void setup() 
{
  Serial.begin(19200);
  delay(1000);
  
}

void serialEvent() 
{
  inputString = "";
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
  }
  analogWrite(6, inputString.toInt()); 
  Serial.println(inputString);
}

void loop() 
{
  delay(100);
  
  
}
