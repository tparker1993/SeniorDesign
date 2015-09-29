volatile int tone1 = 0;
int freq = 0;
volatile long frequency =0;
long prevInterruptTime=0;
long divider = 1000000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pciSetup(7);
  Serial.println("In setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  Serial.println(tone1);

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
       //Serial.println(frequency);
}
