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
volatile int pushVal=0;
volatile short curCRC=0;
char bufferDelay1='0';
char bufferDelay2='0';
char bufferDelay3='0';
int counter7=0;
//Rick was here

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pciSetup(7);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
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
    counter2= 0;
    crc=0xFFFF;
    //delay(1000);
    dontPrint = false;
    endFlagLastByte = true;
    index = 0;
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

    tone1 = 0;
    freq = 0;
    frequency =0;
    prevInterruptTime=0;
    prevToneRead = 0;
    sampleState=1;
    startFlag = 0x7e;
    counter = 0;
    counter2=0;
    prevReading = 0;
    foundInterval = false;
    firstTime=false;
    sampleRate = false; 
    index = 0;
    done = false;
    temp = 0;
    testTime = 0;
    state = false;
    readBit=false;
    buffer1Array [0] = 0;
    buffer1Array [1] = 0;
    buffer1Array [2] = 0;
    buffer1Array [3] = 0;
    buffer1Array [4] = 0;
    buffer1Array [5] = 0;
    buffer1Array [6] = 0;
    buffer1Array [7] = 0;
    j=0;
    hitEndFlag1 = false;
    hitEndFlag2 = false;
    onesInRow =0;
    temp2 = 0; 
    endFlagLastByte = false;
    dontPrint = false;
    crc=0xFFFF;
    lsb=0;
    volatile int pushVal=0;
    curCRC=0;
    counter7=0;
    
    Timer1.setPeriod(104.166);
    Timer1.attachInterrupt(timersetup);  // attaches callback() as a timer overflow interrupt
    Serial.println("\nWaiting for packet . . .");
  
    digitalWrite(9,0);
    
  }
  
  if(firstTime == true){
    digitalWrite(9,1);
    endFlagLastByte = true;
    Timer1.attachInterrupt(shiftTime);
    Timer1.setPeriod(380-(micros() - timeDelay));//416.66
    //Timer1.setPeriod(300);
    buffer1=0;
    counter2=0;
    firstTime=false;
    bufferDelay1='0';
    bufferDelay2='0';
    bufferDelay3='0';
  }
  if(done == true){
    //Timer1.attachInterrupt(nothing);
    done = false;
    //Serial.print("Started with division");
    //Serial.println(division);

    sizeOfMessage = index;
    index = 0;

    Serial.print(message[0][0]);
    Serial.print(message[0][1]);
    Serial.print(message[0][2]);
    Serial.print(message[0][3]);
    Serial.print(message[0][4]);
    Serial.print(message[0][5]);
    Serial.print(message[0][6]);
    Serial.print(message[0][7]);
    Serial.print(message[0][8]);
    Serial.print(message[0][9]);
    Serial.print(message[0][10]);
    Serial.print(message[0][11]);
    Serial.print(message[0][12]);
    Serial.print(message[0][13]);
    Serial.print(message[0][14]);
    Serial.print(message[0][15]);
    Serial.print(message[0][16]);
    Serial.print(message[0][17]);
    Serial.print(message[0][18]);
    Serial.print(message[0][19]);
    Serial.print(message[0][20]);
    Serial.print(message[0][21]);

    if(!dontPrint){
      for(index; index<sizeOfMessage; index++){
        Serial.print(message[0][index]);
      }
      for(index=0;index<(sizeOfMessage-3);index++)
      {
        if(message[0][index]!='~')
        {
          counter7++;
          for(temp=0; temp<8; temp++){
            if(bitRead(message[0][index],temp)==1)
            {
              
              lsb=(crc & 1);
              crc =(crc>>1);
              crc &= 0x7FFF;
              if((lsb^1) == 1)
              {
                crc=(crc^poly); 
              }
            }
            else
            {
              lsb=(crc & 1);
              crc =(crc>>1);
              crc &= 0x7FFF;
              if((lsb^0) == 1)
              {
                crc=(crc^poly); 
              }
            }
          }
        }
      }
      hByte=message[0][sizeOfMessage-2];
      lByte=message[0][sizeOfMessage-3];
      rcrc=((hByte<<8)|lByte);
      //Serial.println("Final");
      //Serial.println(hByte);
      //Serial.println(lByte);
      crc=(~crc);
      //Serial.println(rcrc);
      //Serial.println(crc);
      //Serial.println(counter7);
      //Serial.println(sizeOfMessage);
      counter7=0;
      
      if(crc==rcrc)
      {
        Serial.print("\nCRC Match");
      }
      else
      {
        Serial.print("Put your hands in the ERRRRRRORRR");
      }
    }
    else{
      Serial.println("Failed to find end flag");
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

        pushVal=1;
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

          pushVal=0;
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

      bufferDelay3 = bufferDelay2;
      bufferDelay2 = bufferDelay1;
      bufferDelay1 = buffer1;

      
          for(i=0;i<8;i++){
            bitWrite(buffer1,i,buffer1Array[i]);
          }

        
  
        if(index < 200){
          message[0][index] = buffer1;
          index++;
        }        else{
          Timer1.attachInterrupt(nothing);
          done = true;
          dontPrint = true;
        }
        counter2=0;
        
        if((buffer1^startFlag)==0){
          if(endFlagLastByte == true){
            
            bufferDelay3 = '0';
            bufferDelay2 = '0';
            bufferDelay1 = '0';
          }
          else{
            Timer1.attachInterrupt(nothing);
            done = true;
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
 buffer1 = 0;
}
