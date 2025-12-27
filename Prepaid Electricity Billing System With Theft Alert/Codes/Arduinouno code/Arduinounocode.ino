/*code by RAVITEJA-KADARI*/

#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial gsmSerial(10, 11); // RX, TX pins for GSM module
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define buzzer 7
#define relay  8
#define bt_theft  A0
#define pulse_in 2

char inchar;

int unt_a = 0, unt_b = 0, unt_c = 0, unt_d = 0;
long total_unt = 7;

int price = 0;
long price1 = 0;

int Set = 10;

int pulse = 0;

String phone_no = "+917670889740";

int flag1 = 0, flag2 = 0, flag3 = 0;
unsigned long lastTheftAlertTime = 0;
const unsigned long theftAlertInterval = 1000; // 1 second interval for theft alert

unsigned long lastRechargeSendTime = 0;
const unsigned long rechargeSendInterval = 1000; // Send recharge balance every 1 second

unsigned long lastRechargeReceiveTime = 0;
const unsigned long rechargeReceiveInterval = 1000; // Receive commands from ESP32 every 1 second

unsigned long lastPulseTime = 0;
const unsigned long pulseInterval = 60000; // Interval for decrementing units when load is on (1 minute)

bool relayState = false;

void setup() {
  Serial.begin(9600); // Serial monitor
  gsmSerial.begin(9600); // GSM module
  delay(1000);
  
  pinMode(bt_theft, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pulse_in, INPUT);
  attachInterrupt(0, ai0, RISING);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("WELCOME");
  lcd.setCursor(2, 1);
  lcd.print("Energy Meter");
  digitalWrite(buzzer, HIGH);
  
  Serial.println("Initializing GSM module...");
  delay(1000);
  gsmSerial.println("AT"); // Check if GSM module is responding
  delay(1000);
  while(!gsmSerial.available());
  Serial.println(gsmSerial.readString());
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text mode
  delay(1000);
  gsmSerial.println("AT+CNMI=2,2,0,0,0"); // Enable SMS notifications
  delay(1000);
  Serial.println("GSM module initialized.");

  sendSMS(phone_no, "Welcome To Energy Meter");
  digitalWrite(buzzer, LOW);
  lcd.clear();

  if (EEPROM.read(50) == 0) {}
  else {
    Read();
  }
  EEPROM.write(50, 0);

  pulse = EEPROM.read(10);

  Read();
  if (total_unt > 0) {
    relayState = true;
    digitalWrite(relay, HIGH);
  }
}

void loop() {
  if (Serial.available() > 0) { // Check for commands from ESP32
    char command = Serial.read();
    rechargeFromCommand(command);
  }

  displayLCD();
  sendDataToESP32();
  receiveCommandsFromESP32(); // Receive commands from ESP32

  // Check for low balance alert
  if (total_unt <= 20 && flag1 == 0) {
    flag1 = 1;
    sendSMS(phone_no, "Low balance alert: Please recharge.");
  }

  // Check for power cut
  if (total_unt == 0 && flag2 == 0) {
    flag2 = 1;
    relayState = false;
    digitalWrite(relay, LOW);
    sendSMS(phone_no, "Power cut: Balance exhausted. Please recharge.");
  }

  // Check for theft alert
  if (digitalRead(bt_theft) == 0 && millis() - lastTheftAlertTime >= theftAlertInterval) {
    lastTheftAlertTime = millis();
    sendSMS(phone_no, "Theft Alert: Energy Meter Tampered with!");
  }

  if (millis() - lastRechargeSendTime >= rechargeSendInterval) {
    sendTotalBalanceToESP32(); // Send total recharge balance to ESP32
    sendDataToESP32(); // Send "ri" command to ESP32
    lastRechargeSendTime = millis();
  }

  // Decrement units and price if load is on
  if (relayState && millis() - lastPulseTime >= pulseInterval) {
    lastPulseTime = millis();
    if (total_unt > 0) {
      total_unt--;
      if (total_unt < 0) total_unt = 0; // Ensure units don't go below zero
      price1 = total_unt * Set;
      Write(); // Update EEPROM with new values
    }
  }

  // Turn off relay when balance is 0
  if (total_unt == 0) {
    relayState = false;
    digitalWrite(relay, LOW);
  } else {
    relayState = true;
    digitalWrite(relay, HIGH);
  }

  if (gsmSerial.available()) {
    String msg = gsmSerial.readString();
    Serial.println("Received SMS: " + msg);
    if (msg.indexOf("RECHARGE") != -1) {
      // Parse the message and extract the recharge amount
      int amount = parseRechargeAmount(msg);
      if (amount > 0) {
        recharge(amount);
      } else {
        // Invalid recharge amount
        sendSMS(phone_no, "Invalid recharge amount. Please try again.");
      }
    }
  }

  delay(5);
}

void displayLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Unit:");
  lcd.print(total_unt);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Price:");
  lcd.print(price1);
  lcd.print("   ");

  lcd.setCursor(11, 0);
  lcd.print("Pulse");

  lcd.setCursor(13, 1);
  lcd.print(pulse);
  lcd.print("   ");
}

void rechargeFromCommand(char command) {
  switch (command) {
    case 'r': // Recharge with 10 Rs.
      recharge(10);
      break;
    case 'a': // Recharge with 50 Rs.
      recharge(50);
      break;
    case 'v': // Recharge with 100 Rs.
      recharge(100);
      break;
    default:
      break;
  }
}

void recharge(int amount) {
  price = amount / Set;
  total_unt += price;

  sendSMS(phone_no, "Your Recharge is Done: " + String(amount));

  load_on();
}

void load_on() {
  Write();
  Read();
  relayState = true;
  digitalWrite(relay, HIGH);
  flag1 = 0, flag2 = 0;
}

void sendSMS(String number, String msg) {
  gsmSerial.println("AT+CMGS=\"" + number + "\"");
  delay(500);
  gsmSerial.println(msg);
  delay(500);
  gsmSerial.write(26);
  delay(5000);
}

void Data() {
  gsmSerial.println("AT+CMGS=\"" + phone_no + "\"");
  delay(1000);
  gsmSerial.println("Unit:" + String(total_unt));
  gsmSerial.println("Price:" + String(price1));
  delay(500);
  gsmSerial.write(26);
  delay(5000);
}

void Read() {
  unt_a = EEPROM.read(1);
  unt_b = EEPROM.read(2);
  unt_c = EEPROM.read(3);
  unt_d = EEPROM.read(4);
  total_unt = unt_d * 1000 + unt_c * 100 + unt_b * 10 + unt_a;
  price1 = total_unt * Set;
}

void Write() {
  unt_d = total_unt / 1000;
  total_unt = total_unt - (unt_d * 1000);
  unt_c = total_unt / 100;
  total_unt = total_unt - (unt_c * 100);
  unt_b = total_unt / 10;
  unt_a = total_unt - (unt_b * 10);

  EEPROM.write(1, unt_a);
  EEPROM.write(2, unt_b);
  EEPROM.write(3, unt_c);
  EEPROM.write(4, unt_d);
}

void ai0() {
  if (digitalRead(pulse_in) == 1) {
    pulse = pulse + 1;
    if (pulse > 9) {
      pulse = 0;
      if (total_unt > 0) {
        total_unt = total_unt - 1;
        if (total_unt < 0) total_unt = 0; // Ensure units don't go below zero
      }
      Write();
      Read();
    }
    EEPROM.write(10, pulse);
  }
}

void sendDataToESP32() {
  if (millis() - lastRechargeReceiveTime >= rechargeReceiveInterval) {
    Serial.print("si"); // Command for sending units
    Serial.println(total_unt);
    lastRechargeReceiveTime = millis();
  }
}

void sendTotalBalanceToESP32() {
  Serial.print("ri"); // Command for sending total recharge balance
  Serial.println(price1);
}

int parseRechargeAmount(String msg) {
  // Parse the message to extract the recharge amount
  // You need to define your own parsing logic here based on the format of the incoming message
  // For example, if the message format is "RECHARGE:50", you can extract "50" as the recharge amount
  int index = msg.indexOf(':');
  if (index != -1) {
    String amountStr = msg.substring(index + 1);
    return amountStr.toInt();
  } else {
    return -1; // Invalid recharge amount
  }
}

void receiveCommandsFromESP32() {
  if (millis() - lastRechargeReceiveTime >= rechargeReceiveInterval) {
    // Check for commands from ESP32
    if (Serial.available() > 0) {
      char command = Serial.read();
      // Process the received command
      rechargeFromCommand(command);
    }
    lastRechargeReceiveTime = millis();
  }
}
