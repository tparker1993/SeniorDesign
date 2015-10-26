#include "TimerOne.h"
  //Initialize all variables
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
int toneRead = 0;
boolean trigger = false;

  //This method runs when the arduino is turned on. It specifies the pins the way we want for this lab and the baud rate
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //sets the baud rate
  pinMode(7,INPUT);    //This is the input from the comparator
  pciSetup(7);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  Timer1.initialize(104.166);  //sets the timer to 1/8 the baud rate
  prevInterruptTime=micros();
  
}

void loop() {
  // put your main code here, to run repeatedly:
//this code runs once the first start flag has been found
  if(findStart == true){
    findStart = false;
    firstTime = false;
    
  //reset all variables
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
    toneRead = 0;

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
    digitalWrite(9,0); //Turns LED on (signifies it is ready to read a packet)
    
  }
 //This code runs only the first time through the main loop after reading a start flag
  if(firstTime == true){
    digitalWrite(9,1);
    endFlagLastByte = true;
    Timer1.attachInterrupt(shiftTime);  //this changes the sampling rate to once per bit period
    Timer1.setPeriod(360-(micros() - timeDelay));//416.66  //this delays the sampling to be in the middle of the bit period
//reset the buffers
    buffer1=0;
    counter2=0;
    bufferDelay1='0';
    bufferDelay2='0';
    bufferDelay3='0';
  }

  prevToneRead = 0;
  trigger = false;
  endFlagLastByte = true;
  
 //this while loop runs when we are actually reading information
  while(done == false && firstTime == true){
    
 //this code matches the flow chart provided on ICON for best zero crossing algorithm
    if(tone1 == 0){
      if(prevToneRead == 0){
        if(trigger == false){
          //nothing
        }
        else{
          oneStuff();  //method call to perform proper operations for reading a one into the buffer
        }
      }
      else{
        zeroStuff();  //method call to perform proper operations for reading a zero into the buffer
      }
    }
    else{
      if(prevToneRead == 0){
        zeroStuff();  //method call to perform proper operations for reading a zero into the buffer
      }
      else{
        if(trigger == false){
          //nothing
        }
        else{
          oneStuff();  //method call to perform proper operations for reading a one into the buffer
        }
      }
    }

    
    
//this triggers when a byte of data has been read (one full character)
    if(counter2==8){
      int i=0;
      
      for(i=0;i<8;i++){
        bitWrite(buffer1,i,buffer1Array[i]);  //This writes the char into an array
      }
      if(index < 200){
        message[0][index] = buffer1;  //Put the current character into a 2D array
        index++;
      }        
      else{  //More than the max amount of data characters have passed, so the end flag was missed
        Timer1.attachInterrupt(nothing);
        done = true;
        firstTime=false;
        dontPrint = true;
        Serial.println("Overflow");
      }
      counter2=0;

    //check for a start/end flage
      if((buffer1^startFlag)==0){
        if(endFlagLastByte == true){  
        }
        else{
          Timer1.attachInterrupt(nothing);
          done = true;
          firstTime=false;
          //Serial.println("End Flag Found");
        }
      }
      else{
        endFlagLastByte = false; 
      }
      buffer1 = 0;
      j=0;
     }
  }

 //we have read a full message or received overflow
  if(done == true){
    done = false;
    sizeOfMessage = index;
    index = 0;

    if(!dontPrint){
      for(index; index<sizeOfMessage; index++){
        Serial.print(message[0][index]);    //print out the whole message including the address and FCS
      }


    //This for loop performs the logic of calculating the checksum
      for(index=0;index<(sizeOfMessage-3);index++)
      {
        if(message[0][index]!='~')
        {
          counter7++;
          for(temp=0; temp<8; temp++){
            if(bitRead(message[0][index],temp)==1)
            {
            //perform the logic of pushing a one to the buffer
              lsb=(crc & 1);  //get the least sig bit
              crc =(crc>>1);  //shift it to the right one
              crc &= 0x7FFF; 
              if((lsb^1) == 1)
              {
                crc=(crc^poly);   //exclusive OR the current CRC with the POLY provided
              }
            }
            else  //perform the logic of pushing a one to the buffer
            {
              lsb=(crc & 1); //get the least sig bit
              crc =(crc>>1);  //shift it right one
              crc &= 0x7FFF;
              if((lsb^0) == 1)
              {
                crc=(crc^poly);  //exclusive OR the current CRC with the POLY provided
              }
            }
          }
        }
      }
      hByte=message[0][sizeOfMessage-2];   //get the high byte of the FCS read in from the message
      lByte=message[0][sizeOfMessage-3];   //get the low byte of the FCS read in from the message
      rcrc=((hByte<<8)|lByte);             //combine the low and high byte
      crc=(~crc);                          //negate the check sum
      counter7=0;

    //determine if the checksums match
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
    delay(1000);
    findStart = true;
    firstTime = false;
    sampleState = 1;

  }

}

//This method performs the operations provided in the flow chart on ICON for the process of adding a zero to the buffer
void zeroStuff(){
  Timer1.restart();
  Timer1.attachInterrupt(timerRead);  //reattach the interrupt after restarting it
  Timer1.setPeriod(1250);  //set the sampling rate to 1.5 bit periods 
  
  counter2++;
  
 //account for bit stuffing
  if(onesInRow == 5){
    onesInRow = 0;
    counter2--;
  }
  else{
    buffer1Array[j]=0;
    j++;
    onesInRow = 0;   
    pushVal=0;
  }
  prevToneRead = prevToneRead ^ 1;
  trigger = false;
}

//This method performs the operations provided in the flow chart on ICON for the process of adding a one to the buffer
void oneStuff(){
  counter2++;
  buffer1Array[j]=1;
  j++;
  onesInRow++;
  pushVal=1;

//reset this value because six ones were sent in a row, bit stuffing has happened  
  if(onesInRow == 6){
    onesInRow = 0;
  }

  Timer1.setPeriod(833.33);  //set the sampling rate to 1 bit period
  trigger = false;
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
       frequency = divider/(micros() - prevInterruptTime);  //calculate the current frequency
       if (frequency > 4000) {//4200  //if the frequency represents a high tone set tone1 to one, else set it to zero
           tone1 = 1;
        }
        else{
          tone1 = 0;
        }
      
     prevInterruptTime=micros();   //keep track of this tone
}

//this interrupt uses 8 buffers to read in a start flag
void timersetup(){
  
    digitalWrite(8,sampleRate);
    sampleRate = !sampleRate;
    switch(sampleState){
      case 1:
         if(prevTone1==tone1){   //this implements the change on zero algorithm
            buffer1<<=1;         //shift the buffer by one
            buffer1 |= 1;        //add one to the buffer
            if((buffer1^startFlag)==0){  //check for start flag
              prevToneRead=tone1;
              firstTime = true;
              division = 1;
            }
            prevTone1=tone1;
         }else{   //perform the logic of a change (adding a zero to the buffer)
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
      sampleState=1;   //reset which buffer to place the next value in
    }
    
}

void clearBuffers(){
  buffer1=0;
  buffer2=0;
  buffer3=0;
  buffer4=0;
}

//this interrupt is active once a start flag is read and it is reading in actual information
void timerRead(){
  trigger = true;   //flag to show we have entered this interrupt
  digitalWrite(8,sampleRate);
  sampleRate = !sampleRate;
}

//changes the sample rate to once per bit period
void shiftTime(){
  digitalWrite(8,sampleRate);
  sampleRate = !sampleRate;
  Timer1.setPeriod(833.333);
  Timer1.attachInterrupt(timerRead);
}

void nothing(){
 buffer1 = 0;
}
