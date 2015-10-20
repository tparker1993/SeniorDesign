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
volatile short crc=0xFFFF;
volatile const short poly=0x8408;
volatile int lsb=0;
volatile short rcrc;
volatile unsigned char lByte;
volatile unsigned char hByte;
volatile int z=0;
//Rick was here

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
    crc=0xFFFF;
    //delay(1000);
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
    //Serial.print("Started with division");
    //Serial.println(division);

    sizeOfMessage = index;
    index = 0;

    if(!dontPrint){
      for(index; index<sizeOfMessage; index++){
        Serial.print(message[0][index]);
      }
      lByte=message[0][sizeOfMessage-2];
      hByte=message[0][sizeOfMessage-3];
      rcrc=((hByte<<8)|lByte);
      Serial.println(hByte);
      Serial.println(lByte);
      Serial.println(rcrc);
      Serial.println(crc);
      
      if(crc==rcrc)
      {
        Serial.print("Correct CRC");
      }
      else
      {
        Serial.print("Put your hands in the ERRRRRRORRR");
      }
    }

    dontPrint = false;
    endFlagLastByte = true;
    index = 0;
    findStart = true;
    firstTime = false;
    sampleState = 1;

  }

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
  counter2++;

    if(!done){
     if(prevToneRead==tone1){
        
        //if(k<=690){
          //bitArray[k]=1;
        //}
        buffer1Array[j]=1;
        j++;
        onesInRow++;


        lsb=(crc & 1);
        crc =(crc>>1);
        crc &= 0x7FFF;
        if((lsb^1) == 1)
        {
          crc=(crc^poly); 
        }
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

          lsb=(crc & 1);
          crc=(crc>>1);
          crc &= 0x7FFF;
          if((lsb^0) == 1)
          {
            crc=(crc^poly); 
          }
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
  
        if(index < 200){
          message[0][index] = buffer1;
          index++;
        }
        else{
          Serial.println("Failed to locate end flag");
          done = true;
          dontPrint = true;
          Timer1.attachInterrupt(nothing);
        }
        
        counter2=0;
        
        if((buffer1^startFlag)==0){
          if(endFlagLastByte == true){
          }
          else{
            done = true;
            crc=(~crc);
            Timer1.attachInterrupt(nothing);
          }
        }
        else{
          endFlagLastByte = false;
        }
        buffer1 = 0;
        j=0;
     }
  }
}

void shiftTime(){
  digitalWrite(8,sampleRate);
  sampleRate = !sampleRate;
  Timer1.setPeriod(833.333);
  Timer1.attachInterrupt(timerRead);
}

void nothing(){
}
