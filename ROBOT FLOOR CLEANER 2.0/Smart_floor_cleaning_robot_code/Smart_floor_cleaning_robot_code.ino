/*code by RAVITEJA-KADARI*/

#include <AFMotor.h>

// Pin definitions for motors and components
#define MOTOR1_PIN1 3   // Motor 1 IN1
#define MOTOR1_PIN2 4   // Motor 1 IN2
#define MOTOR2_PIN1 5   // Motor 2 IN1
#define MOTOR2_PIN2 6   // Motor 2 IN2
#define CLEANER_PIN    7   // Cleaning motor
#define WATER_PUMP_PIN 8   // Water pump

// Bluetooth Serial
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX

AF_DCMotor motor1(1);  // Motor 1
AF_DCMotor motor2(2);  // Motor 2

void setup() {
  // Initialize motors, cleaning motor, and water pump
  motor1.setSpeed(255);  // Max speed
  motor2.setSpeed(255);  // Max speed
  pinMode(CLEANER_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);

  // Start Bluetooth Serial communication
  BTserial.begin(9600); // Default baud rate of Bluetooth module
}

void loop() {
  if (BTserial.available()) {
    char command = BTserial.read();  // Read the incoming Bluetooth command
    
    // Forward command
    if (command == 'F') {
      moveForward();
    }
    // Backward command
    else if (command == 'B') {
      moveBackward();
    }
    // Left command
    else if (command == 'L') {
      turnLeft();
    }
    // Right command
    else if (command == 'R') {
      turnRight();
    }
    // Stop command
    else if (command == 'S') {
      stopMovement();
    }
    // Start cleaning
    else if (command == 'C') {
      startCleaning();
    }
    // Stop cleaning
    else if (command == 'X') {
      stopCleaning();
    }
  }
}

void moveForward() {
  motor1.setSpeed(255);  // Max speed for motor 1
  motor2.setSpeed(255);  // Max speed for motor 2
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void moveBackward() {
  motor1.setSpeed(255);  // Max speed for motor 1
  motor2.setSpeed(255);  // Max speed for motor 2
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

void turnLeft() {
  motor1.setSpeed(255);  // Max speed for motor 1
  motor2.setSpeed(255);  // Max speed for motor 2
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

void turnRight() {
  motor1.setSpeed(255);  // Max speed for motor 1
  motor2.setSpeed(255);  // Max speed for motor 2
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void stopMovement() {
  motor1.setSpeed(0);  // Stop motor 1
  motor2.setSpeed(0);  // Stop motor 2
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void startCleaning() {
  digitalWrite(CLEANER_PIN, HIGH);  // Start cleaning motor
  digitalWrite(WATER_PUMP_PIN, HIGH);  // Start water pump
}

void stopCleaning() {
  digitalWrite(CLEANER_PIN, LOW);  // Stop cleaning motor
  digitalWrite(WATER_PUMP_PIN, LOW);  // Stop water pump
}
