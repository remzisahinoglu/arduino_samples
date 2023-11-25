/*
board : Arduino Uno
shield: Ethernet Shield
yazan : Remzi Şahinoğlu
tarih : 15.09.2016
amaç  : Bu program arduinoyu server olarak başlatır.
Telnet 23. porttan bağlanılıp data alır ve yazar.

*/

#include <SPI.h>
#include <Ethernet.h>

const int servis_valf = 8;
const int imdat_valf = 7;

const int full_strok = 6;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(111, 112, 113, xxx);                         // boştaki bir ip adresi
IPAddress myDns(111,112,113, 94);
IPAddress gateway(111, 112, 113, 100);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(23);                                // telnet defaults to port 23

void setup() 
{
  Ethernet.begin(mac, ip, myDns, gateway, subnet);        // initialize the ethernet device
  server.begin();                                         // start listening for clients
  
  Serial.begin(9600);

  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());

  pinMode(servis_valf, OUTPUT);
  pinMode(imdat_valf, OUTPUT);

  pinMode(full_strok, INPUT);
}

void loop() 
{
  EthernetClient client = server.available();                   // wait for a new client:

  if (client) 
  {
    if (client.available() > 0) 
    {   
      char inChar = client.read();                               // read the bytes incoming from the client:

      if (inChar == 'u'){ server.write("1;23232;4;23;4;test running;"); }
      if (inChar == 's'){ digitalWrite(servis_valf, HIGH); }                                  // servise hava ver
      if (inChar == 'i'){ digitalWrite(imdat_valf, HIGH); }                                   // imdata hava ver
      if (inChar == 'r'){ digitalWrite(servis_valf, LOW); digitalWrite(imdat_valf, LOW); }    // boşalt
      
    }
  }

  


  
}



