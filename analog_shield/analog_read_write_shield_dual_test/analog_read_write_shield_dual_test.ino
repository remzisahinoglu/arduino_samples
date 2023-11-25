/*
prg adı: analog_read_write_shield_dual_test
tarih: 18.8.2015
yazan: Remzi ŞAHİNOĞLU

bu program istasyon arduinolarına bağlı olan dual analog shield modulunun 
test edilmesi için yazılmıştır

*/
String inputString = "";
int data = 0;

void setup() {

  pinMode(0, INPUT);
  pinMode(1, INPUT);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);
  Serial.println("analog shield - dual programi basladi");

  delay(1000);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void loop() {
  delay(100);
  
  while (Serial.available()) {
     char inChar = (char)Serial.read();
     inputString += inChar;
     
     if (inChar == ' ') {
       data = inputString.toInt();
       inputString = "";
     }

     switch(inChar){
       case 's':
         Serial.print("servis pwm: ");
         Serial.println(data);
         analogWrite(10, data); // yazılan değer 8-bit çözünürlükte
         inputString = "";
         break;
       case 'i':
         Serial.print("imdat pwm: ");
         Serial.println(data);
         analogWrite(11, data); // yazılan değer 8-bit çözünürlükte
         inputString = "";
         break;

       case 'q':
         Serial.println("servis valf");
         if(digitalRead(6) == 1){digitalWrite(6, LOW);}else{digitalWrite(6, HIGH);}
         inputString = "";
         break;
       case 'w':
         Serial.println("servis kilit valf");
         if(digitalRead(7) == 1){digitalWrite(7, LOW);}else{digitalWrite(7, HIGH);}
         inputString = "";
         break;
       case 'e':
         Serial.println("imdat valf");
         if(digitalRead(8) == 1){digitalWrite(8, LOW);}else{digitalWrite(8, HIGH);}
         inputString = "";
         break;
       case 'r':
         Serial.println("imdat kilit valf");
         if(digitalRead(9) == 1){digitalWrite(9, LOW);}else{digitalWrite(9, HIGH);}
         inputString = "";
         break;
     }
  } 
}
