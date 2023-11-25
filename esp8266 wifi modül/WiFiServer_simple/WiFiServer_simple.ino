/* wifi bilgileri */
const String wifiAdi = "FuckTheWorld";
const String wifiSifresi = "musmula159";

const String serverIP = "192.168.0.17";
const String port = "23";

String PCinputString = "";
boolean PCstringComplete = false;

String WiFiinputString = "";
boolean WiFistringComplete = false;

void setup()
{
  Serial.begin(115200);                               // pc ilebağlantısı bu porttan olacak
  Serial1.begin(115200);                            // wifi bağlantısı bu porttan olacak  
  delay(500);

  

}


void loop()
{
  delay(25);
  while (Serial.available())
  { 
    delay(1);
    char inChar = (char)Serial.read();
    PCinputString += inChar;
        
    //if (inChar == '\n')
    //{
      PCstringComplete = true;
    //}
  }
  
  
  if (PCstringComplete == true)
  {
    PCstringComplete = false;
    Serial1.println(PCinputString);
    PCinputString = "";
  }

  delay(25);
  while (Serial1.available())
  { 
    delay(1);
    char inChar = (char)Serial1.read();
    WiFiinputString += inChar;
        
    WiFistringComplete = true;

  }

  if (WiFistringComplete == true)
  {
    WiFistringComplete = false;
    Serial.println(WiFiinputString);
    WiFiinputString = "";
  }
  
}















