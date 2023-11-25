// bipolar step motor kontrol uygulaması
// Remzi Şahinoğlu
// 22.09.2014

 
// pin tanımlamaları
int mA1 = 8;
int mA2 = 9;
int mB1 = 10;
int mB2 = 11;
int ileri = 2;
int geri = 3;
int delayTime = 2;

// pin giriş çıkış ayarlamaları
void setup() {
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  pinMode(ileri, INPUT);
  pinMode(geri, INPUT);
}
void Step1(){              // 1 adım
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  delay(delayTime);
}
void Step2(){              // 2 adım
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
  delay(delayTime);
}
void Step3(){              // 3 adım
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
  delay(delayTime);
}
void Step4(){              // 4 adım
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  delay(delayTime);
}
// kısır dögüye gir
void loop() {
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
  
  if(digitalRead(ileri)==0){
    Step1();
    Step2();
    Step3();
    Step4();
  }
  if(digitalRead(geri)==0){
    Step4();
    Step3();
    Step2();
    Step1();
  }
}
