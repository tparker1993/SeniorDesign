int tone1 = 0;
int freq = 0;
float prevInterruptTime;

void setup() {
  // put your setup code here, to run once:
  pciSetup(7);
}

void loop() {
  // put your main code here, to run repeatedly:

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
        if ((millis() - prevInterruptTime) > freq) {
           tone1 = 1;
        }
        else{
          tone1 = 0;
        }
}
