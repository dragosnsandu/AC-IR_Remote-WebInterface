/*
 Name:		NANO_IR_Slave.ino
 Created:	13-Sep-18 11:18:57
 Author:	Dragos Sandu
*/

#include <IRremote.h>
#include <Wire.h>

IRsend irSend;

unsigned long int receivedCode = 0;
unsigned long int oldReceivedCode = 0;
const int ledPin = 3;

void setup() {
	Wire.begin(6);
	Wire.onReceive(receiveFromESP);
	pinMode(ledPin, OUTPUT);
	Serial.begin(9600);
	Serial.println("I2C Slave ready!");
}

void loop() {
	if ( receivedCode != oldReceivedCode ) {
		digitalWrite(ledPin, HIGH);
		irSend.sendNEC(receivedCode, 32); // 38KHz
		digitalWrite(ledPin, LOW);
		oldReceivedCode = receivedCode;
	}
}

void receiveFromESP(int count) {
	unsigned char codeBuf[4];
	int i = 0;
	while (0 < Wire.available()) { // loop through all I2C messages
		codeBuf[i] = Wire.read(); // receive byte
		i++;
	}
	receivedCode = (long)codeBuf[0] << 24;
	receivedCode += (long)codeBuf[1] << 16;
	receivedCode += (long)codeBuf[2] << 8;
	receivedCode += (long)codeBuf[3];
	Serial.println(receivedCode);
	Serial.println(oldReceivedCode);
}
