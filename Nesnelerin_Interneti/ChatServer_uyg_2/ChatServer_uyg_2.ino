/*
board : Arduino Uno
shield: Ethernet Shield
yazan : Remzi Şahinoğlu
tarih : 13.09.2016
amaç  : Bu program sensorlerden gelen bilgiyi okuyup ağ içindeki
verilen ip ile server kurup httpde yayınlar


*/

#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };            // Enter a MAC address and IP address for your controller below
IPAddress ip(192, 168, 0, 177);                                 // evdeki modemin adresi 192.168.0.1, verilecek adres bundan büyük olmalı

EthernetServer server(23);                                      // (port 23 is default for telnet):

void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for debugging
    
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client

                Serial.print(c);
                server.write(c);
                delay(500);
            }
        }
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    }
}
