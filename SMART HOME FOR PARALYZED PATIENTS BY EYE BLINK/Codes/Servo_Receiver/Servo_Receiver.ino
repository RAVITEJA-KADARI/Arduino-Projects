/*code by RAVITEJA-KADARI*/

#include <SPI.h>      //SPI library for communication with the nRF24L01+
#include "RF24.h"  //The main library of the nRF24L01+
#include <Servo.h> // servo library


RF24 radio (7, 8); // CE,CSN

Servo lampSwitch;

//Create a pipe addresses for  communication
const uint64_t pipe = 0xE8E8F0F0E1LL;

int readingSensor;


boolean closeEyes = false;

void setup() {
  Serial.begin(9600);
  lampSwitch.attach(3);
   lampSwitch.write(30);  
  radio.begin();                    //Start the nRF24 communicate
  radio.openReadingPipe(1, pipe);   //Sets the address of the transmitter to which the program will receive data.
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&readingSensor, sizeof(readingSensor));
    
  }

  if (readingSensor == 0 ) {
    closeEyes =! closeEyes;
    delay(1000);
    Serial.println(closeEyes);
  }
  if (closeEyes == true) {   //turn off the lamp
    lampSwitch.write(70);
    delay(100);
  } else {
    lampSwitch.write(0);       //turn on the lamp
    delay(100);
  }
}
