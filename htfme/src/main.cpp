#include <Arduino.h>

#define TX 1 
#define RX 0
#define S1I 6 
#define S2I 5
#define S1O 4 
#define S2O 3

//s1, mode=0, UART : s2, mode=1, FREQ
struct state_
{ 
  bool enabled = true;
  uint8_t mode = -1;
};

struct state_ state; 


void setup() 
{
  initSwitch();
  initLed(); 
}

void initSwitch() 
{
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
  ;; 
}

void initUART()
{
  sendPulse();
  pinMode(TX, INPUT);
  pinMode(RX, INPUT);
}

void loop() {

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

}
