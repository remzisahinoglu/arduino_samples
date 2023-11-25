/*
 
 */


const int buttonPin = 2;
const int ledPin =  13;

int buttonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  digitalWrite(ledPin, LOW);
}

void loop()
{
  if (buttonState == 1)
  {
    if(digitalRead(buttonPin) == HIGH)
    {
      buttonState = 0;  
      digitalWrite(ledPin, HIGH);
    }    
  }
}
