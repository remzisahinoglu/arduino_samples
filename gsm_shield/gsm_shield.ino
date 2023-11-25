/*
 SMS sender
 
 This sketch, for the Arduino GSM shield,sends an SMS message 
 you enter in the serial monitor. Connect your Arduino with the 
 GSM shield and SIM card, open the serial monitor, and wait for 
 the "READY" message to appear in the monitor. Next, type a 
 message to send and press "return". Make sure the serial 
 monitor is set to send a newline when you press return.
 
 Circuit:
 * GSM shield 
 * SIM card that can send SMS
 
 created 25 Feb 2012
 by Tom Igoe
 
 This example is in the public domain.
 
 http://arduino.cc/en/Tutorial/GSMExamplesSendSMS
 
 */

// Include the GSM library
#include <GSM.h>

#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

void setup()
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("SMS Messages Sender");

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("GSM initialized");
}

void loop()
{
  char numara[] = "05344552861";
  // send the message
  sms.beginSMS(numara);
  sms.print("test");
  sms.endSMS(); 
  Serial.println("\nCOMPLETE!\n");
}

