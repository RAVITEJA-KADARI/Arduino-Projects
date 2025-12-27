/*code by RAVITEJA-KADARI*/

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "***************" // Add Your Blynk id
#define BLYNK_TEMPLATE_NAME "*****************" // blynk name
#define BLYNK_AUTH_TOKEN "******************" // blynk token

char auth[] = "**************";  // Your Blynk authentication token

// Your WiFi credentials
char ssid[] = " WIFI NAME";
char pass[] = "WIFI PASSWORD";
//#define RXD2 17 // ESP32 RX to Arduino Uno TX
//#define TXD2 16 // ESP32 TX to Arduino Uno RX
#define VIRTUAL_PIN_RECHARGE_10RS V1
#define VIRTUAL_PIN_RECHARGE_50RS V2
#define VIRTUAL_PIN_RECHARGE_100RS V3
#define VIRTUAL_PIN_TOTAL_BALANCE V4
#define VIRTUAL_PIN_UNITS V5


void receiveDataFromArduino() {
  String receivedString = Serial.readStringUntil('\n');
  
  if (receivedString.startsWith("si")) {
    int units = receivedString.substring(2).toInt();
    Blynk.virtualWrite(VIRTUAL_PIN_UNITS, units);
  } else if (receivedString.startsWith("ri")) {
    int totalBalance = receivedString.substring(2).toInt();
    Blynk.virtualWrite(VIRTUAL_PIN_TOTAL_BALANCE, totalBalance);
  }
}


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Call the function to receive data from Arduino Uno
  Serial.setTimeout(50);
}

void loop() {
  Blynk.run();
  receiveDataFromArduino();
}

BLYNK_WRITE(VIRTUAL_PIN_RECHARGE_10RS) {
  // Send 'r' command to Arduino Uno for 10 Rs. recharge
  Serial.write('r');
}

BLYNK_WRITE(VIRTUAL_PIN_RECHARGE_50RS) {
  // Send 'a' command to Arduino Uno for 50 Rs. recharge
  Serial.write('a');
}

BLYNK_WRITE(VIRTUAL_PIN_RECHARGE_100RS) {
  // Send 'v' command to Arduino Uno for 100 Rs. recharge
  Serial.write('v');
}
