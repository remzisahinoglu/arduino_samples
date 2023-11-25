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

EthernetServer server(80);                                      // (port 80 is default for HTTP):

void setup() 
{  
  Serial.begin(9600);                                           // Open serial communications and wait for port to open:

  Ethernet.begin(mac, ip);                                      // start the Ethernet connection and the server:
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() 
{ 
  EthernetClient client = server.available();                   // listen for incoming clients
  if (client) 
  {
    Serial.println("new client");
    boolean currentLineIsBlank = true;                          // an http request ends with a blank line
    while (client.connected()) 
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 15");    // refresh the page automatically every 15 sec, manual yaptırmak için pasif yapıldı
          client.println();
          client.println("<!DOCTYPE HTML>");
          // htlm kodunu bu satırdan sonra yaz
          
          client.println("<html>");
          client.println("<head>");
          //client.println("<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>");
          client.println("<title>Omur Test Sistemleri</title>");
          client.println("<style>");
          client.println("table{width:100%;}");
          client.println("table, th, td{ border: 1px solid black; border-collapse: collapse; }");
          client.println("th, td{ padding: 1px; text-align: left; }");
          client.println("table#t01 tr:nth-child(even){ background-color: #eee; }");
          client.println("table#t01 tr:nth-child(odd) { background-color:#fff; }");
          client.println("table#t01 th { background-color: black; color: white; }");
          client.println("</style>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>ARFESAN A.Ş.</h1>");
          client.println("<h1>ÖMÜR TEST SİSTEMLERİ</h1>");
          client.println("<table>");
          client.println("<tr>");
          client.println("<th>İstasyon No:</th>");
          client.println("<th>Arfesan No:</th>");
          client.println("<th>Yapılan Çevrim:</th>");
          client.println("<th>Hedef Çevrim:</th>");
          client.println("<th>Test Fazı:</th>");
          client.println("<th>Başlangıç Tarihi:</th>");
          client.println("<th>Bitiş Tarihi:</th>");
          client.println("<th>Durum:</th>");
          client.println("</tr>");
          client.println("<tr><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>2</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>3</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>4</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>5</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>6</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>7</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>8</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>9</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>10</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>11</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>12</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>13</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>14</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>15</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>16</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>17</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>18</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>19</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>20</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>21</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>22</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>23</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>24</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>25</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>26</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>27</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>28</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>29</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>30</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("<tr><td>31</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>");
          client.println("</table>");
          client.println("</body>");
          client.println("</html>");
          
          break;
        }
        if (c == '\n')
        {          
          currentLineIsBlank = true;                      // you're starting a new line
        } 
        else if (c != '\r') 
        {        
          currentLineIsBlank = false;                     // you've gotten a character on the current line
        }
      }
    }
    
    delay(1);                                           // give the web browser time to receive the data   
    client.stop();                                      // close the connection:  
    Serial.println("client disconnected");
  }
}

