/*code by RAVITEJA-KADARI*/

#include <Servo.h>

// Define the pin numbers for the LDRs and Servo
int ldr1Pin = A0;  // LDR 1
int ldr2Pin = A1;  // LDR 2
int servoPin = 9;  // Servo motor connected to pin 9

Servo solarServo;  // Create a Servo object

void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);

  // Initialize the servo
  solarServo.attach(servoPin);

  // Set LDR pins as input
  pinMode(ldr1Pin, INPUT);
  pinMode(ldr2Pin, INPUT);
}

void loop() {
  // Read the LDR values
  int ldr1Value = analogRead(ldr1Pin);
  int ldr2Value = analogRead(ldr2Pin);

  // Print the LDR values for debugging
  Serial.print("LDR 1: ");
  Serial.print(ldr1Value);
  Serial.print("  LDR 2: ");
  Serial.println(ldr2Value);

  // If LDR 1 detects more light (left side)
  if (ldr1Value > ldr2Value) {
    solarServo.write(90);  // Move the servo to the left
  }
  // If LDR 2 detects more light (right side)
  else if (ldr2Value > ldr1Value) {
    solarServo.write(180);  // Move the servo to the right
  }
  // If both LDRs detect similar light (centered)
  else {
    solarServo.write(90);  // Keep the servo in the center
  }

  delay(1000);  // Small delay to allow the servo to move and stabilize
}
