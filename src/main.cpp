#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <WiFiUdp.h>

#define PORT 1488

const char* ssid = "Unicorn_2.4GHz";
const char* pass = "Stark_13";


WiFiUDP UDP;
IPAddress server_ip;
bool isClientConfigured = false;

char packet[1024];

void setup() {
	Serial.begin(9600);
	// Connect to WiFi
	WiFi.begin(ssid, pass);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print("*");
	}

	Serial.println("");
	Serial.println("WiFi connection Successful");
	Serial.println("The IP Address of ESP8266 Module is: ");

	UDP.begin(PORT);
	Serial.print(WiFi.localIP());// Print the IP address
	
}




void loop() {
	server_ip.fromString("192.168.13.255");

	int packetSize = UDP.parsePacket();
  	if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, 1024);
    if (len > 0)
      packet[len] = '\0';
    Serial.print("Packet received: ");
    Serial.println(packet);
	}


	int isSuccess;
	isClientConfigured = true;
	if (isClientConfigured)
	{		
		isSuccess = UDP.beginPacket (server_ip, PORT);
		Serial.print("Begin Packet : ");
		Serial.println(isSuccess);
		isSuccess = UDP.write("Hello from Wemos!!");
		Serial.print("Write : ");
		Serial.println(isSuccess);
		isSuccess = UDP.endPacket();
		Serial.print("End Packet : ");
		Serial.println(isSuccess);
	}

	delay(5000);

}