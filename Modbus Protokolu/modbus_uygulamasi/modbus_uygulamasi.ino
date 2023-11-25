
int gonder = 0;

void setup()
{
  Serial.begin(9600);

}

void loop()
{
  while(Serial.available())
  {
    gonder = 1;
    
    char inChar = (char)Serial.read();
    delay(5);
  }

  
  if(gonder == 1)
  {
    gonder = 0;
 
    Serial.write(0x01); Serial.flush(); delayMicroseconds(1750);
    Serial.write(0x03); Serial.flush(); delayMicroseconds(1750);
    Serial.write(0x02); Serial.flush(); delayMicroseconds(1750);
    Serial.write(0x00); Serial.flush(); delayMicroseconds(1750);
    Serial.write(0x64); Serial.flush(); delayMicroseconds(1750);
    Serial.write(0xB9); Serial.flush(); delayMicroseconds(1750);
    Serial.write(0xAF); Serial.flush(); delayMicroseconds(1750);

  }

}


