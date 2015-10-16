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
bool firstTime=false;
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
volatile int buffer1Array [8];
volatile int j=0;
boolean hitEndFlag1 = false;
boolean hitEndFlag2 = false;
int onesInRow =0;
int division = 0;
int frequencies[100];
int temp2 = 0; 
boolean endFlagLastByte = false;
boolean findStart = true;
boolean dontPrint = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pciSetup(7);
  pinMode(8,OUTPUT);
  Serial.println("In setup");

   Timer1.initialize(104.166);
   prevInterruptTime=micros();
  
}

void loop() {
  // put your main code here, to run repeatedly:
 /* delay(500);
  for(int i=0;i<7;i++){
    Serial.println(bitRead(buffer1,i));
  }*/

  if(findStart == true){
    findStart = false;
    firstTime = false;
    prevToneRead=0;
    division = 1;
    done = false;
    counter = 0;
    Timer1.setPeriod(104.166);
    Timer1.attachInterrupt(timersetup);  // attaches callback() as a timer overflow interrupt
    Serial.println("Find Start");

    
  }
  
  if(firstTime == true){
    endFlagLastByte = true;
    Timer1.attachInterrupt(shiftTime);
    Timer1.setPeriod(380-(micros() - timeDelay));//416.66
    //Timer1.setPeriod(300);
    buffer1=0;
    counter2=0;
    firstTime=false;
  }

  if(done == true){
    Timer1.attachInterrupt(nothing);
    done = false;
    Serial.print("Started with division");
    Serial.println(division);
    
    //Timer1.stop();
    sizeOfMessage = index;
    index = 0;

    if(!dontPrint){
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
    }

    dontPrint = false;
    endFlagLastByte = true;
    index = 0;
    findStart = true;
    firstTime = false;
    sampleState = 1;
    buffer1 = 0;
    buffer2 = 0;
    buffer3 = 0;
    buffer4 = 0;
    buffer5 = 0;
    buffer6 = 0;
    buffer7 = 0;
    buffer8 = 0;
    prevTone1 = 0;
    prevTone2 = 0;
    prevTone3 = 0;
    prevTone4 = 0;
    prevTone5 = 0;
    prevTone6 = 0;
    prevTone7 = 0;
    prevTone8 = 0;
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
       if (frequency > 4200) {//3800
           tone1 = 1;
        }
        else{
          tone1 = 0;
        }
      
     prevInterruptTime=micros();
  
}
void timersetup(){
  
    digitalWrite(8,sampleRate);
    sampleRate = !sampleRate;
    switch(sampleState){
      case 1:
         if(prevTone1==tone1){
            buffer1<<=1;
            buffer1 |= 1;
            if((buffer1^startFlag)==0){
              prevToneRead=tone1;
              firstTime = true;
              division = 1;
            }
            prevTone1=tone1;
         }else{
            buffer1<<=1;
            buffer1 |= 0;
           if((buffer1^startFlag)==0){
              prevToneRead=tone1;
              division = 1;
              firstTime = true;   
            }
            prevTone1=tone1;
         }
         break;
        case 2:
         if(prevTone2==tone1){
            buffer2<<=1;
            buffer2 |= 1;
            if((buffer2^startFlag)==0){
              prevToneRead=tone1;
              division = 2;
              firstTime = true;
  
            }
            prevTone2=tone1;
         }else{
            buffer2<<=1;
            buffer2 |= 0;
            if((buffer2^startFlag)==0){
              prevToneRead=tone1;
              division = 2;
              firstTime = true;
            }
            prevTone2=tone1;
         }
          break;
         case 3:
         if(prevTone3==tone1){
            buffer3<<=1;
            buffer3 |= 1;
            if((buffer3^startFlag)==0){
              prevToneRead=tone1;          
              firstTime = true;
              division = 3;
            }
            prevTone3=tone1;
         }else{
            buffer3<<=1;
            buffer3 |= 0;
            if((buffer3^startFlag)==0){
              prevToneRead=tone1;
              division = 3;
              firstTime = true;
            }
            prevTone3=tone1;
         }
          break;
         case 4:
         if(prevTone4==tone1){
            buffer4<<=1;
            buffer4 |= 1;
            if((buffer4^startFlag)==0){
              prevToneRead=tone1;
              firstTime = true;
              division = 4;
            }
            prevTone4=tone1;
         }else{
            buffer4<<=1;
            buffer4 |= 0;
            if((buffer4^startFlag)==0){
              prevToneRead=tone1;
              division = 4;
              firstTime = true;
            }
            prevTone4=tone1;
         }
          break;
         case 5:
         if(prevTone5==tone1){
            buffer5<<=1;
            buffer5 |= 1;
            if((buffer5^startFlag)==0){
              prevToneRead=tone1;
              firstTime = true;
              division = 5;
            }
            prevTone5=tone1;
         }else{
            buffer5<<=1;
            buffer5 |= 0;
            if((buffer5^startFlag)==0){
              prevToneRead=tone1;
              division = 5;
              firstTime = true;
            }
            prevTone5=tone1;
         }
          break;
         case 6:
         if(prevTone6==tone1){
            buffer6<<=1;
            buffer6 |= 1;
            if((buffer6^startFlag)==0){
              prevToneRead=tone1;
              firstTime = true;
              division = 6;
            }
            prevTone6=tone1;
         }else{
            buffer6<<=1;
            buffer6 |= 0;
            if((buffer6^startFlag)==0){
              prevToneRead=tone1;
              division = 6;
              firstTime = true;
            }
            prevTone6=tone1;
         }
          break;
         case 7:
         if(prevTone7==tone1){
            buffer7<<=1;
            buffer7 |= 1;
            if((buffer7^startFlag)==0){
              prevToneRead=tone1;
              firstTime = true;
              division = 7;
            }
            prevTone7=tone1;
         }else{
            buffer7<<=1;
            buffer7 |= 0;
            if((buffer7^startFlag)==0){
              prevToneRead=tone1;
              division = 7;
              firstTime = true;
            }
            prevTone7=tone1;
         }
          break;
         case 8:
         if(prevTone8==tone1){
            buffer8<<=1;
            buffer8 |= 1;
            if((buffer8^startFlag)==0){
              prevToneRead=tone1;
              firstTime = true;
              division = 8;
            }
            prevTone8=tone1;
         }else{
            buffer8<<=1;
            buffer8 |= 0;
            if((buffer8^startFlag)==0){
              prevToneRead=tone1;
              division = 8;
              firstTime = true;
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
          
          //if(k<=690){
            //bitArray[k]=1;
          //}
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
            //if(k<=690){
            //  bitArray[k]=0;
            //}
            
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
            }
            //Serial.print("-");

            
            // = 0;
        
          //Serial.print("Buffer char is ");
          //Serial.print(buffer1);
          if(index < 200){
            message[0][index] = buffer1;
            index++;
          }
          else{
            Serial.println("Failed to locate end flag");
            done = true;
            dontPrint = true;
          }
          
          counter2=0;
          
          if((buffer1^startFlag)==0){
            if(endFlagLastByte == true){
            }
            else{
              done = true;
            }
          }
          else{
            endFlagLastByte = false;
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
  digitalWrite(8,sampleRate);
  sampleRate = !sampleRate;
  Timer1.setPeriod(833.333);
  Timer1.attachInterrupt(timerRead);
}

void nothing(){
}

