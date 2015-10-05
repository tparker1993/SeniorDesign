#include "TimerOne.h"

volatile int tone1 = 0;
int freq = 0;
volatile long frequency =0;
long prevInterruptTime=0;
long divider = 1000000;
//float sample=207.452;
<<<<<<< HEAD
float sample=208.333;
=======
float sample=208.2;
>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
volatile int prevTone1 = 0,prevTone2 = 0,prevTone3 = 0,prevTone4 = 0,prevToneRead;
volatile int sampleState=1;
volatile char buffer1,buffer2,buffer3,buffer4;
volatile char startFlag = 0x7e;
volatile int counter = 0;
volatile int prevReading = 0;
volatile bool foundInterval = false;
bool firstTime=true;
<<<<<<< HEAD
bool firstTime2=true;
volatile bool sampleRate = false;
volatile char message[1][1000];
int index = 0;
bool done = false;
int sizeOfMessage;
int temp = 0;
=======
volatile float testTime = 0;
volatile bool state = false;
>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pciSetup(7);
  pinMode(8,OUTPUT);
<<<<<<< HEAD
  Serial.println("In setup");

  Timer1.initialize(sample);
  Timer1.attachInterrupt(timersetup);  // attaches callback() as a timer overflow interrupt
=======
  digitalWrite(7,HIGH);
  Serial.println("In setup");

  Timer1.initialize();
  Timer1.attachInterrupt(timersetup,sample);  // attaches callback() as a timer overflow interrupt
>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
  foundInterval = false;
  
}

void loop() {
  // put your main code here, to run repeatedly:
 /* delay(500);
  for(int i=0;i<7;i++){
    Serial.println(bitRead(buffer1,i));
  }*/

  while(foundInterval == false){
    
  }
  if(firstTime == true){
    
    buffer1=0;
    counter=0;
    firstTime=false;
  }

  if(done == true && firstTime2 == true){
    Timer1.stop();
    sizeOfMessage = index;
    index = 0;
    for(index; index<=sizeOfMessage; index++){
      Serial.print(message[1][index]);
    }
    firstTime2 = false;
  }
  
  
  
  //Serial.println("a break");
  

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

       if (frequency > 3500) {
           tone1 = 1;
        }
        else{
          tone1 = 0;
        }
       prevInterruptTime=micros();
      // Serial.println(tone1);
}
void timersetup(){
<<<<<<< HEAD
    digitalWrite(8,sampleRate);
    sampleRate = !sampleRate;
    counter++;
=======
    counter++;
    digitalWrite(8, state);
    state = !state;
>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
    switch(sampleState){
      case 1:
         if(prevTone1==tone1){
            buffer1<<=1;
            buffer1 |= 1;
            if((buffer1^startFlag)==0){
<<<<<<< HEAD
              //Serial.println("start flag Detected 1 ");
              //Serial.println(counter);
              //Serial.print(buffer1);
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
=======
              Serial.println("start flag Detected 1 ");
              Serial.println(counter);
              

>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
            }
            prevTone1=tone1;
         }else{
         // Serial.println(buffer1+50);
            buffer1<<=1;
            //Serial.println(buffer1+50);
            buffer1 |= 0;
            //Serial.println(buffer1+50);
           if((buffer1^startFlag)==0){
              //Serial.println("Start Flag Detected 1*");
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
              
            }
           // Serial.println(buffer1);
            prevTone1=tone1;
         }
         break;
        case 2:
         if(prevTone2==tone1){
            buffer2<<=1;
            buffer2 |= 1;
            if((buffer2^startFlag)==0){
<<<<<<< HEAD
              //Serial.println("Start Flag Detected 2 ");
              //Serial.println(counter);
              //Serial.print(buffer2);
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
=======
              Serial.println("Start Flag Detected 2 ");
              Serial.println(counter);
              
  
>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
            }
            prevTone2=tone1;
         }else{
            buffer2<<=1;
            buffer2 |= 0;
            if((buffer2^startFlag)==0){
              //Serial.println("Start Flag Detected 2*");
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
            }
            prevTone2=tone1;
         }
          break;
         case 3:
         if(prevTone3==tone1){
            buffer3<<=1;
            buffer3 |= 1;
            if((buffer3^startFlag)==0){
<<<<<<< HEAD
              //Serial.println("Start Flag Detected 3 ");
              //Serial.println(counter);
              //Serial.print(buffer3);
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
=======
              Serial.println("Start Flag Detected 3 ");
              Serial.println(counter);
              

>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
            }
            prevTone3=tone1;
         }else{
            buffer3<<=1;
            buffer3 |= 0;
            if((buffer3^startFlag)==0){
              //Serial.println("Start Flag Detected 3*");
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
            }
            prevTone3=tone1;
         }
          break;
         case 4:
         if(prevTone4==tone1){
            buffer4<<=1;
            buffer4 |= 1;
            if((buffer4^startFlag)==0){
<<<<<<< HEAD
              //Serial.println("Start Flag Detected 4 ");
              //Serial.println(counter);
              //Serial.print(buffer4);
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
=======
              Serial.println("Start Flag Detected 4 ");
              Serial.println(counter);
              //Serial.print(buffer4);
              //foundInterval=true;
              //prevToneRead=tone1;
              //float sample=829.808;
              //Timer1.initialize(sample);
              //////Timer1.attachInterrupt(timerRead);
>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
            }
            prevTone4=tone1;
         }else{
            buffer4<<=1;
            buffer4 |= 0;
            if((buffer4^startFlag)==0){
              //Serial.println("Start Flag Detected 4*");
              foundInterval=true;
              prevToneRead=tone1;
              float sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              Timer1.setPeriod(sample);
              Timer1.attachInterrupt(timerRead);
            }
            prevTone4=tone1;
         }
          break;
    }
    sampleState++;
    if(sampleState==5){
      sampleState=1;
    }
    
}

void clearBuffers(){
  buffer1=0;
  buffer2=0;
  buffer3=0;
  buffer4=0;
}

void timerRead(){
<<<<<<< HEAD
  digitalWrite(8,sampleRate);
  sampleRate = !sampleRate;
  counter++;
  //Serial.println(counter);
  
   if(prevToneRead==tone1){
      buffer1>>=1;
      buffer1 |= 0x80;
      //Serial.print("pushing 1");
      //Serial.print("buffer1 is ");
      //for(temp=7; temp>=0; temp--){
      //  Serial.print(bitRead(buffer1,temp));
      //}
      //Serial.println(buffer1);
      //Serial.println("");
      if((buffer1^startFlag)==0){
        Serial.println("found second flag");
        Timer1.stop();
        done = true;
      }
   }else{
      buffer1>>=1;
      buffer1 |= 0x00;
      //Serial.print("pushing 0");
      //Serial.print("buffer1 is ");
      //buffer1 = 0x39;
      //for(temp=7; temp>=0; temp--){
      //  Serial.print(bitRead(buffer1,temp));
      //}
      //Serial.println(buffer1);
      //Serial.println("");
      if((buffer1^startFlag)==0){
        Serial.println("found second flag");
        Timer1.stop();
        done = true;
      }
   }
   prevToneRead = tone1;

 
   if(counter==8){

      buffer1 = 0x39;
      //Serial.print("Buffer char is ");
      //Serial.println(buffer1);
      message[0][index] = buffer1;
      index++;
      counter=0;
      if((buffer1^startFlag)==0){
        Serial.println("found second flag");
        Timer1.stop();
        done = true;
        
      }
      buffer1=0;
=======
  Timer1.resume();
  counter++;
  
   if(prevTone1==tone1){
      buffer1>>=1;
      buffer1 |= 0;
      Serial.print("0");
   }else{
      buffer1>>=1;
      buffer1 |= 128;
      Serial.print("1");
   }

   

   if(counter==8){
      Serial.print(buffer1);
      buffer1=0;
      counter=0;
      if((buffer1^startFlag)==0){
        Timer1.stop();
        Serial.println("found second flag");
      }
>>>>>>> 113b37f7c2de1744159bb1a0741a3a96d651179a
   }

   //Serial.print(tone1);
}



