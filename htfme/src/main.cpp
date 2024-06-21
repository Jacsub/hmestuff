#include <Arduino.h>
#include <FreqMeasure.h>

#define TX 1 
#define RX 0
#define S1I 6 
#define S2I 5
#define S1O 4 
#define S2O 3
#define RELAY 9 

//s1, mode=0, UART : s2, mode=1, FREQ
struct state_
{ 
  bool enabled = true;
  uint8_t mode = -1;
};

struct state_ state; 

void initSwitch() 
{
  pinMode(RELAY, OUTPUT);
  pinMode(S1I, INPUT);
  pinMode(S2I, INPUT);
}
void initLed()
{
  pinMode(S1O, OUTPUT);
  pinMode(S2O, OUTPUT);
  digitalWrite(S2O, HIGH);
  digitalWrite(S1O, HIGH);
}

void setup() 
{
  initSwitch();
  initLed(); 
}

void sendPulse()
{
   pinMode(RX, OUTPUT);

   digitalWrite(RX, LOW);
   delay(500);
   digitalWrite(RX, HIGH);

   pinMode(S1I, INPUT);
   pinMode(S2I, INPUT);

}

void initFreq()
{
  digitalWrite(RELAY, HIGH);
  sendPulse();
  FreqMeasure.begin();
}

void initUART()
{
  FreqMeasure.end();
  digitalWrite(RELAY, LOW);
  sendPulse();
  pinMode(TX, INPUT);
  pinMode(RX, INPUT);
}

void freqLoop()
{
  ;;
}

void loop() {

  /*  Button stuff  */
  if (!digitalRead(S1I)) //Button normally high
  {

    if (state.mode == 0) //Ignore any button press if it's already activated
    {
        return;
    }

    state.enabled = false;
    state.mode = 0;
    digitalWrite(S1O, LOW);
    digitalWrite(S2O, HIGH);
  }

  if (!digitalRead(S2I)) //Button normally high
  {
    
    if (state.mode == 1) //Ignore any button press if it's already activated
    {
      return;
    }

    state.enabled = false;
    state.mode = 1;
    digitalWrite(S2O, LOW);
    digitalWrite(S1O, HIGH);
  }
  /*  Button stuff  */

  if (!state.enabled) //If mode change, do init functions
  {

    switch(state.mode)
    {
     case 0: 
        initUART(); 
        break;
     case 1: 
        initFreq();
         break; 
    }

    state.enabled = true;
  }

  if(state.mode) // Check for frequency measurements if in that mode;
  {
    freqLoop(); 
  }

}
