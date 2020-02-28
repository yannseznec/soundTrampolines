/* Trampoline specific Teensy MIDI code
 *  by Yann Seznec
*/




// the MIDI channel number to send messages
const int channel = 5;
//


int const numDigPins = 1; // switches you are using (how many areas in the trampoline, for example)
int currentDig[numDigPins];
int digitalpin[] = {
 0,1,2,3,4  // which digital pins to use for sending note values
};
int digitalpitch[] = {
  60,62,64,66,71 // which midi notes to send from the digitalpins pins
  }; 





void setup() {


 
    for (int i = 0; i < numDigPins; i++) {
    pinMode(digitalpin[i], INPUT_PULLUP);
  }
  Serial.begin(38400);

}

void loop() {


// digital pins sending notes
  for (int i = 0; i < numDigPins; i++) {
    if (digitalRead(digitalpin[i]) == 1 && currentDig[i] == 0) {
      usbMIDI.sendNoteOff(digitalpitch[i], 100, channel); 
      currentDig[i] = 1;
    }  
    if (digitalRead(digitalpin[i]) == 0  && currentDig[i] == 1) {
      usbMIDI.sendNoteOn(digitalpitch[i], 100, channel);
      currentDig[i] = 0;
    }  
  }


  
  
  // i think if you remove these last two lines everything breaks and things are sad and people cry
  while (usbMIDI.read()); // read and discard any incoming MIDI messages
   delay(5); 
}
