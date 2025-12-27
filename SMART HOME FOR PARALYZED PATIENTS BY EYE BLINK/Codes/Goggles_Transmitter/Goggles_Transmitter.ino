/*code by RAVITEJA-KADARI*/

#include <Servo.h>
Servo myservo; 
const byte servostart = 72; //servo motor start point
int distanceleft = 0;
int distanceright = 0;
long t, cm;
void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, INPUT);
  myservo.attach(11);
  start();
  rotete(); 
}
void loop() {
  getdistance();
  int leftdistance = 0;
  int rightdistance = 0;
 
  if (cm <= 40) {
    robostop();
    Serial.println("robo stop");
    delay(100);
    backward();
    Serial.println("robo backward");
    delay(300);
    robostop();
    Serial.println("robo stop");
    delay(200);
    leftdistance = leftsee();
    Serial.println(leftdistance);
    delay(200);
    rightdistance = rightsee();
    Serial.println(rightdistance);
 
    if (leftdistance >= rightdistance) {
      turnleft();
      delay(500);
      robostop();
      Serial.println("turnleft");
    } else {
      turnright();
      delay(500);
      robostop();
      Serial.println("turnright");
    }
  } else {
    forward();
    Serial.println("forward");
  } 
}
 
void start() {
  //myservo.write(servostart);
  delay(3000);
  for (int a = 0; a < 4; a++) {
    myservo.write(servostart);
    delay(50);
    myservo.write(40);
    delay(50);
    myservo.write(90);
    delay(50);
    myservo.write(servostart);
  }
}
 
void rotete() {
  delay(500);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  delay(2000);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
 
void forward() {
  digitalWrite(5, HIGH );
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void backward() {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
}
void robostop() {
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}
void turnleft() {
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
void turnright() {
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
int leftsee() {
  myservo.write(servostart);
  delay(1000);
  myservo.write(155);
  delay(1000);
  distanceleft = getdistance();
  //Serial.println(distanceleft);
  myservo.write(servostart);
  return distanceleft;
}
int rightsee() {
  myservo.write(servostart);
  delay(1000);
  myservo.write(5);
  delay(1000);
  distanceright = getdistance();
  //Serial.println(distanceright);
  myservo.write(servostart);
  return distanceright;
}
int getdistance() {
  digitalWrite(2, LOW);
  delayMicroseconds(4);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  t = pulseIn(4, HIGH);
  cm = t / 29 / 2;
  //Serial.println(cm);
  return cm;
}