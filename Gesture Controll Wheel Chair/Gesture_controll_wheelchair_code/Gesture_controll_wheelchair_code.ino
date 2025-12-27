// Gesture-controlled wheelchair code by "RAVITEJA-KADARI"
//controll using mobile bluetooth app
//gesture from mobile app

// Pin definitions for motor control
int lm1 = 8; // Left motor output 1
int lm2 = 9; // Left motor output 2
int rm1 = 10; // Right motor output 1
int rm2 = 11; // Right motor output 2

// Variable to store the command from Bluetooth
char d = 0;

void setup() {
  // Set motor pins as output
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  
  // Initialize serial communication with Bluetooth
  Serial.begin(38400);
  
  // Initially stop the wheelchair
  stop();
}

void loop() {
  // Check if data is available from Bluetooth
  if (Serial.available() > 0) {
    d = Serial.read(); // Read the command from Bluetooth
    
    // Perform actions based on the received command
    if (d == 'F') {
      forward();
    }
    if (d == 'B') {
      backward();
    }
    if (d == 'L') {
      left();
    }
    if (d == 'R') {
      right();
    }
    if (d == 'S') {
      stop(); // Stop the wheelchair
    }
  }
}

// Move forward
void forward() {
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

// Move backward
void backward() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}

// Turn left
void left() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH);
  digitalWrite(rm2, LOW);
}

// Turn right
void right() {
  digitalWrite(lm1, HIGH);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, HIGH);
}

// Stop the wheelchair
void stop() {
  digitalWrite(lm1, LOW);
  digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW);
  digitalWrite(rm2, LOW);
}
