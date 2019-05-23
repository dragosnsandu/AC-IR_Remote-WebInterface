/*
 Name:		ESP_IR_WebInterface.ino
 Created:	12-Sep-18 08:23:40
 Author:	Dragos Sandu
*/

#include <Wire.h>
#include <WiFi.h>
#include <ESP32WebServer.h>
#include <HTTPClient.h>

String code, prefix, receivedCode;
WiFiClient client;
unsigned long codeReceived;
unsigned char codeBuf[4];
char buf[11];

const char* ssid = "********";
const char* password = "*********";

void setup() {

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}

	//irReceiver.enableIRIn(); //for reading IR codes 
	Wire.begin(4, 5); //4 for data, 5 for clock
	Serial.begin(9600);
	Serial.println("I2C Master on ESP32 ready!");
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

		HTTPClient http;

		http.begin("https://ir-remote-webinterface.azurewebsites.net/command"); //Specify the URL
		int httpCode = http.GET(); //Make the request

		if (httpCode > 0) { //Check for the returning code
			String payload = http.getString();
			payload.toCharArray(buf,sizeof(buf));
			codeReceived = strtoul(buf, NULL, 10);
		}

		else {
			Serial.println("Error on HTTP request");
		}

		http.end(); //Free the resources
	
	}

	codeBuf[0] = (int)((codeReceived >> 24) & 0xFF);
	codeBuf[1] = (int)((codeReceived >> 16) & 0xFF);
	codeBuf[2] = (int)((codeReceived >> 8) & 0XFF);
	codeBuf[3] = (int)((codeReceived & 0XFF));

	Wire.beginTransmission(6); // transmit to device #6
	Wire.write(codeBuf,4);              // sends one byte to Nano via I2C
	Wire.endTransmission();    // stop transmitting

	delay(2000);
}
