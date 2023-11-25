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
#include <SD.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };            // Enter a MAC address and IP address for your controller below
IPAddress ip(192, 168, 0, 177);                                 // evdeki modemin adresi 192.168.0.1, verilecek adres bundan büyük olmalı

EthernetServer server(80);                                      // (port 80 is default for HTTP):

File webFile;

void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for debugging
    
    // initialize SD card
    Serial.println("SD card ayarlaniyor...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card ayarlanmasinda hata!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card baslatildi");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - index.htm file bulunamadi!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - index.htm file bulundu.");
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    
                    // send web page
                    webFile = SD.open("index.htm");        // open web page file
                    if (webFile) {
                        while(webFile.available()) {
                            client.write(webFile.read()); // send web page to client
                        }
                        webFile.close();
                    }
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            }
        }
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    }
}
