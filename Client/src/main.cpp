#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>


IPAddress ip(192,168,1,177);
IPAddress server(192,168,1,125); 

byte MAC[] = {0xAC, 0xBD, 0x1F, 0x9E, 0x56, 0xEF}; 

EthernetClient client; 

void setup()
{
	Ethernet.begin(MAC, ip); 
	Serial.begin(9600);

    if(client.connect(server, 5000))
	{
		Serial.println("Successful connection to server"); 
	}
	
}

void loop()
{
	if(client.available())
	{
		char c = client.read(); 
		Serial.print(c);
	}
} 
