#include <Arduino.h>
#include <FreqMeasure.h>

void setup()
{
  FreqMeasure.begin(); 
  Serial.begin(9600); 
} 

double sum = 0;
int count = 0; 

void loop()
{
 if(FreqMeasure.available())
 {
    sum += FreqMeasure.read();
    count++;
    if(count > 50)
    {
       float frequency = FreqMeasure.countToFrequency(sum / count);
       Serial.println(frequency); 
       sum = 0;
       count = 0;
    }
 }
}