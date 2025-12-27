/*Code by RAVITEJA_KADARI*/

#include <SoftwareSerial.h>

// HC-05 connections
// HC-05 TX -> Arduino RX (D10)
// HC-05 RX -> Arduino TX (D11) through voltage divider
SoftwareSerial BT(9, 8);  // RX, TX

#define RELAY_PIN 3  // Relay control pin

String btData = "";  // Stores incoming Bluetooth commands

void setup() {
  Serial.begin(9600);    // Serial Monitor for debugging
  BT.begin(9600);        // HC-05 Bluetooth default baud rate

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Start with relay OFF

  Serial.println("System Ready");
}

void loop() {
  // Read data from Bluetooth
  while (BT.available()) {
    char c = BT.read();
    if (c != '\n' && c != '\r') {  // Ignore line breaks
      btData += c;
    }
  }

  // If a command is received
  if (btData.length() > 0) {
    btData.trim();  // Remove extra spaces
    Serial.print("Received command: ");
    Serial.println(btData);  // Print received command to Serial Monitor

    if (btData == "FF1") {            // Button sends "ON"
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Relay turned ON");
    } 
    else if (btData == "N1") {      // Button sends "OFF"
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Relay turned OFF");
    } else {
      Serial.println("Unknown command");
    }

    btData = "";  // Clear buffer for next command
  }
}
