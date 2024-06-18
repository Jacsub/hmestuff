#include <Arduino.h>

#define OUT 3


int freq = 440; 

void setup() 
{
  Serial.begin(9600); 
	pinMode(OUT, OUTPUT);
	tone(OUT, freq);
}



void loop() 
{
  if(Serial.available()) 
  {
    freq = Serial.parseInt(); 
    if(freq)
    {
       tone(OUT, freq); 
    }
  }
}
