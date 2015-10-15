#include "TimerOne.h"

volatile int tone1 = 0;
int freq = 0;
volatile long frequency =0;
long prevInterruptTime=0;
long timeDelay;
long divider = 1000000;
//float sample=207.452;
float sample=104.166;
//float sample=208.333;
volatile int prevTone1 = 0,prevTone2 = 0,prevTone3 = 0,prevTone4 = 0,prevTone5 = 0,prevTone6 = 0,prevTone7 = 0,prevTone8 = 0,prevToneRead;
volatile int sampleState=1;
volatile char buffer1,buffer2,buffer3,buffer4,buffer5,buffer6,buffer7,buffer8;
volatile char startFlag = 0x7e;
volatile int counter = 0,counter2=0;
volatile int prevReading = 0;
volatile bool foundInterval = false;
bool firstTime=true;
bool firstTime2=true;
volatile bool sampleRate = false;
volatile char message[1][200];
int index = 0;
bool done = false;
int sizeOfMessage;
int temp = 0;
volatile float testTime = 0;
volatile bool state = false;
volatile bool readBit=false;
//volatile int bitArray [700];
volatile int k=0;
volatile int buffer1Array [8];
volatile int j=0;
boolean hitEndFlag1 = false;
boolean hitEndFlag2 = false;
int onesInRow =0;
int division = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pciSetup(7);
  pinMode(8,OUTPUT);
  Serial.println("In setup");

  Timer1.initialize(sample);
  Timer1.attachInterrupt(timersetup);  // attaches callback() as a timer overflow interrupt
  digitalWrite(7,HIGH);
  prevInterruptTime=micros();
  
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

    Timer1.attachInterrupt(shiftTime);
    Timer1.setPeriod(380-(micros() - timeDelay));//416.66
    
    buffer1=0;
    counter=0;
    firstTime=false;
  }

  if(done == true && firstTime2 == true){
    Serial.print("Started with division");
    Serial.println(division);
    
    Timer1.stop();
    sizeOfMessage = index;
    index = 0;
    for(index; index<=sizeOfMessage; index++){
      /*Serial.print(bitRead(message[0][index],7));
      Serial.print(bitRead(message[0][index],6));
      Serial.print(bitRead(message[0][index],5));
      Serial.print(bitRead(message[0][index],4));
      Serial.print(bitRead(message[0][index],3));
      Serial.print(bitRead(message[0][index],2));
      Serial.print(bitRead(message[0][index],1));
      Serial.print(bitRead(message[0][index],0));
      Serial.print("-");*/
      Serial.print(message[0][index]);
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
{      
  
  //Serial.println("In interrupt");
       frequency = divider/(micros() - prevInterruptTime);
       if (frequency > 4000) {//3800
           tone1 = 1;
        }
        else{
          tone1 = 0;
        }
      
     prevInterruptTime=micros();
    // Serial.println(tone1);
  
}
void timersetup(){
    digitalWrite(8,sampleRate);
    sampleRate = !sampleRate;
    counter++;
    switch(sampleState){
      case 1:
         if(prevTone1==tone1){
            buffer1<<=1;
            buffer1 |= 1;
            if((buffer1^startFlag)==0){
              //Serial.println("start flag Detected 1 ");
              //Serial.println(counter);
              //Serial.print(buffer1);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Timer1.start();
              
              

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
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Timer1.start();
              division = 1;
              
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
              //Serial.println("Start Flag Detected 2 ");
              //Serial.println(counter);
              //Serial.print(buffer2);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              
  
            }
            prevTone2=tone1;
         }else{
            buffer2<<=1;
            buffer2 |= 0;
            if((buffer2^startFlag)==0){
              //Serial.println("Start Flag Detected 2*");
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              division = 2;
            }
            prevTone2=tone1;
         }
          break;
         case 3:
         if(prevTone3==tone1){
            buffer3<<=1;
            buffer3 |= 1;
            if((buffer3^startFlag)==0){
              //Serial.println("Start Flag Detected 3 ");
              //Serial.println(counter);
              //Serial.print(buffer3);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();           

            }
            prevTone3=tone1;
         }else{
            buffer3<<=1;
            buffer3 |= 0;
            if((buffer3^startFlag)==0){
              //Serial.println("Start Flag Detected 3*");
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              division = 3;
            }
            prevTone3=tone1;
         }
          break;
         case 4:
         if(prevTone4==tone1){
            buffer4<<=1;
            buffer4 |= 1;
            if((buffer4^startFlag)==0){
              //Serial.println("Start Flag Detected 4 ");
              //Serial.println(counter);
              //Serial.print(buffer4);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Serial.print(buffer4);
              //foundInterval=true;
              //prevToneRead=tone1;
              //float sample=829.808;
              //Timer1.initialize(sample);
              //////Timer1.attachInterrupt(timerRead);
            }
            prevTone4=tone1;
         }else{
            buffer4<<=1;
            buffer4 |= 0;
            if((buffer4^startFlag)==0){
              //Serial.println("Start Flag Detected 4*");
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Timer1.start();
              division = 4;
            }
            prevTone4=tone1;
         }
          break;
         case 5:
         if(prevTone5==tone1){
            buffer5<<=1;
            buffer5 |= 1;
            if((buffer5^startFlag)==0){
              //Serial.println("Start Flag Detected 4 ");
              //Serial.println(counter);
              //Serial.print(buffer4);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Serial.print(buffer4);
              //foundInterval=true;
              //prevToneRead=tone1;
              //float sample=829.808;
              //Timer1.initialize(sample);
              //////Timer1.attachInterrupt(timerRead);
            }
            prevTone5=tone1;
         }else{
            buffer5<<=1;
            buffer5 |= 0;
            if((buffer5^startFlag)==0){
              //Serial.println("Start Flag Detected 4*");
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Timer1.start();
              division = 5;
            }
            prevTone5=tone1;
         }
          break;
         case 6:
         if(prevTone6==tone1){
            buffer6<<=1;
            buffer6 |= 1;
            if((buffer6^startFlag)==0){
              //Serial.println("Start Flag Detected 4 ");
              //Serial.println(counter);
              //Serial.print(buffer4);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Serial.print(buffer4);
              //foundInterval=true;
              //prevToneRead=tone1;
              //float sample=829.808;
              //Timer1.initialize(sample);
              //////Timer1.attachInterrupt(timerRead);
            }
            prevTone6=tone1;
         }else{
            buffer6<<=1;
            buffer6 |= 0;
            if((buffer6^startFlag)==0){
              //Serial.println("Start Flag Detected 4*");
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Timer1.start();
              division = 6;
            }
            prevTone6=tone1;
         }
          break;
         case 7:
         if(prevTone7==tone1){
            buffer7<<=1;
            buffer7 |= 1;
            if((buffer7^startFlag)==0){
              //Serial.println("Start Flag Detected 4 ");
              //Serial.println(counter);
              //Serial.print(buffer4);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Serial.print(buffer4);
              //foundInterval=true;
              //prevToneRead=tone1;
              //float sample=829.808;
              //Timer1.initialize(sample);
              //////Timer1.attachInterrupt(timerRead);
            }
            prevTone7=tone1;
         }else{
            buffer7<<=1;
            buffer7 |= 0;
            if((buffer7^startFlag)==0){
              //Serial.println("Start Flag Detected 4*");
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Timer1.start();
              division = 7;
            }
            prevTone7=tone1;
         }
          break;
         case 8:
         if(prevTone8==tone1){
            buffer8<<=1;
            buffer8 |= 1;
            if((buffer8^startFlag)==0){
              //Serial.println("Start Flag Detected 4 ");
              //Serial.println(counter);
              //Serial.print(buffer4);
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Serial.print(buffer4);
              //foundInterval=true;
              //prevToneRead=tone1;
              //float sample=829.808;
              //Timer1.initialize(sample);
              //////Timer1.attachInterrupt(timerRead);
            }
            prevTone8=tone1;
         }else{
            buffer8<<=1;
            buffer8 |= 0;
            if((buffer8^startFlag)==0){
              //Serial.println("Start Flag Detected 4*");
              foundInterval=true;
              prevToneRead=tone1;
              sample=833.33;
              //float sample=829.80x8;
              //Timer1.detachInterrupt();
              //Timer1.stop();
              //Timer1.start();
              division = 8;
            }
            prevTone8=tone1;
         }
          break;
    }
     timeDelay = prevInterruptTime;
    
    sampleState++;
    if(sampleState==9){
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
  digitalWrite(8,sampleRate);
  sampleRate = !sampleRate;
  //readBit=true;
 /* digitalWrite(8,sampleRate);
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
   }else{
      buffer1>>=1;
      buffer1 |= 0x00;
      //Serial.print("pushing 0");
      //Serial.print("buffer1 is ");
    
      //for(temp=7; temp>=0; temp--){
       // Serial.print(bitRead(buffer1,temp));
      //}
      //Serial.println(buffer1);
      //Serial.println("");
   }
   prevToneRead = tone1;
   if(counter==8){
      //Serial.print("Buffer char is ");
      Serial.print(buffer1);
      message[0][index] = buffer1;
      index++;
      counter=0;
      if((buffer1^startFlag)==0){
        Serial.println("found second flag");
        Timer1.stop();
        done = true;
        
      }
      buffer1 = 0;
   }*/

        counter2++;
      
       if(prevToneRead==tone1){
          buffer1>>=1;
          buffer1 |= 0x80;
          
          //if(k<=690){
            //bitArray[k]=1;
          //}
          k++;
          buffer1Array[j]=1;
          j++;
          onesInRow++;
          
          //Serial.print("pushing 1");
          //Serial.print("buffer1 is ");
          //for(temp=7; temp>=0; temp--){
          //  Serial.print(bitRead(buffer1,temp));
          //}
          //Serial.println(buffer1);
          //Serial.println("");

          if(onesInRow == 6){
            onesInRow = 0;
            //flag
          }
       }
       else{

          if(onesInRow == 5){
            onesInRow = 0;
            counter2--;
            //bit stuffing

            
          }
          else{

            buffer1>>=1;
            buffer1 |= 0x00;
            //if(k<=690){
            //  bitArray[k]=0;
            //}
            
            k++;
            buffer1Array[j]=0;
            j++;

            onesInRow = 0;
          }
        
          
          //Serial.print("pushing 0");
          //Serial.print("buffer1 is ");
        
          //for(temp=7; temp>=0; temp--){
           // Serial.print(bitRead(buffer1,temp));
          //}
          //Serial.println(buffer1);
          //Serial.println("");
       }
       prevToneRead = tone1;
    
       if(counter2==8){
        int i=0;

            for(i=0;i<8;i++){
              bitWrite(buffer1,i,buffer1Array[i]);
              //Serial.print(bitRead(buffer1,i));
              
            }
            //Serial.print("-");

            
            // = 0;
        
          if(k==1000){
            //Serial.println("");
            
            //for(i=0;i<690;i++){
              //if(i%8 == 0){
                //Serial.print("-");
              //}
              //Serial.print(bitArray[i]);
            //}
            Timer1.stop();
            done = true;
          }
          //Serial.print("Buffer char is ");
          //Serial.print(buffer1);
          message[0][index] = buffer1;
          index++;
          counter2=0;
          if((buffer1^startFlag)==0){
           // Serial.println("found second flag");
            //Timer1.stop();
            //done = true;
            
          }
          buffer1 = 0;
          j=0;
         // buffer1 |= 0x00;
          //counter++;
       }
       //readBit=false;
       //prevToneRead = tone1;

   
}

void shiftTime(){
  Timer1.setPeriod(833.333);
  Timer1.attachInterrupt(timerRead);
}

