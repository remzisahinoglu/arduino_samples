/*
yazan: remzi şahinoğlu
tarih: 15.07.2016
board: arduino uno

bu program analog pine bağlı değeri okuuyp serialdan yazar

*/


//********************** BAŞLANGIÇ AYARLARI *****************************//
void setup()
{
  Serial.begin(9600);
  delay(1000);

  pinMode(2, INPUT_PULLUP);
}

//************************** ANA PROGRAM ********************************//
void loop()
{
  if(digitalRead(2) == 0)
  {
    Serial.println(analogRead(0)); 
    delay(200);
  }
  
}









