#include "TimerOne.h"

volatile int tone1 = 0;
int freq = 0;
volatile long frequency =0;
long prevInterruptTime=0;
long divider = 1000000;
float sample=208.3;
volatile int prevTone1 = 0;
volatile int sampleState=1;
volatile char buffer1,buffer2,buffer3,buffer4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pciSetup(7);
  Serial.println("In setup");

  Timer1.initialize(sample);
  Timer1.attachInterrupt(timersetup);  // attaches callback() as a timer overflow interrupt
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(1);
  //Serial.println(tone1);

}


// Pin change interrupt setup
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

// Pin change interrupt
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{      //Serial.println("In interrupt");
       frequency = divider/(micros() - prevInterruptTime);

       if (frequency > 3000) {
           tone1 = 1;
        }
        else{
          tone1 = 0;
        }
       prevInterruptTime=micros();
       Serial.println(tone1);
}
void timersetup(){
    switch(sampleState){
      case 1:
         if(prevTone1==tone1){
            buffer1<<1;
            buffer1 |= 1 << 0;
         }else{
            buffer1<<1;
            buffer1 |= 1 << 1;
         }
         break;
        case 2:
         if(prevTone1==tone1){
            buffer2<<1;
            buffer2 |= 1 << 0;
         }else{
            buffer2<<1;
            buffer2 |= 1 << 1;
         }
          break;
         case 3:
         if(prevTone1==tone1){
            buffer3<<1;
            buffer3 |= 1 << 0;
         }else{
            buffer3<<1;
            buffer3 |= 1 << 1;
         }
          break;
         case 4:
         if(prevTone1==tone1){
            buffer4<<1;
            buffer4 |= 1 << 0;
         }else{
            buffer4<<1;
            buffer4 |= 1 << 1;
         }
          break;
    }
    prevTone1=tone1;
    sampleState++;
    if(sampleState==5){
      sampleState=1;
    }
    
}


