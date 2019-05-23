/*
 Name:		ESP_IR_WebInterface.ino
 Created:	12-Sep-18 08:23:40
 Author:	Dragos Sandu
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include <IRremote.h>

String code, prefix;
WiFiClient client;
unsigned long codeReceived;
unsigned long oldcodeReceived;
unsigned char codeBuf[4];
char buf[11];

const char* ssid = SSID;
const char* password = PASSWORD;

const byte IR_LED = 15;

IRsend irsend(IR_LED);

void setup() {

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}

	//irReceiver.enableIRIn(); //for reading IR codes 
	Serial.begin(9600);
}

//AC Codes:
//Turn on - 2172573225 - 817ED629
//Night mode - 2172540585 - 817E56A9
//C/F - 2172532425 - 817E36C9
//Down - 2172524265 - 817E16E9
//UP - 2172560985 - 817EA659
//Mode - 2172544665 - 817E6699
//Angle - 2172577305 - 817EE619
//Timer - 2172556905 - 817E9669
//Air - 2172528345 - 817E26D9

void loop() {

	//for reading IR codes
	//if (irReceiver.decode(&results)) {
	//	Serial.println(results.rawlen);
	//	for (int i = 0; i < results.rawlen; i++) {
	//		rawData[i] = results.rawbuf[i];
	//	}
	//	for (int i = 0; i < results.rawlen; i++) {
	//		Serial.print(rawData[i]);
	//		Serial.print(",");
	//	}
	//	irReceiver.resume();
	//}
	
	if ((WiFi.status() == WL_CONNECTED)) {
    Serial.println("Connected");
		HTTPClient http;

		http.begin("https://ir-remote-webinterface.azurewebsites.net/command"); //Specify the URL
		int httpCode = http.GET(); //Make the request

		if (httpCode > 0) { //Check for the returning code
			String payload = http.getString();
			payload.toCharArray(buf,sizeof(buf));
      oldcodeReceived = codeReceived;
			codeReceived = strtoul(buf, NULL, 10);
      Serial.println(codeReceived);
      if (codeReceived != oldcodeReceived) {
        irsend.sendNEC(codeReceived, 32);
      }
        
  	}
  	else {
			Serial.println("Error on HTTP request");
		}

		http.end(); //Free the resources
	
	}

	delay(2000);
}
