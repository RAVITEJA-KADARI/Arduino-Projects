
/*Code by RAVITEJA_KADARI*/

#define BLYNK_TEMPLATE_ID "*************"
#define BLYNK_TEMPLATE_NAME "Weather prediction system"
#define BLYNK_AUTH_TOKEN "*******************"

// Include the library files
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <SFE_BMP180.h>

#define TH 5
#define Rain 36

// Variables for pressure
double T, P;
char status;

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// BMP180 object
SFE_BMP180 bmp;

DHT dht(TH, DHT11);
BlynkTimer timer;

// WiFi credentials
char ssid[] = "realme 8 5G";
char pass[] = "123456789";

int displayStep = 0;  // To cycle through displays

void setup() {
  Serial.begin(115200);

  // Start Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize sensors
  bmp.begin();
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(Rain, INPUT);
  analogReadResolution(12);

  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Weather Monitor");
  Serial.println("Welcome to Weather Monitoring System");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  Serial.println("Initializing...");
  delay(2000);
  lcd.clear();
}

// Display Temperature
void displayTemperature() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("DHT sensor error (Temp)");
    lcd.setCursor(0,0);
    lcd.print("Temp sensor err");
    return;
  }

  Blynk.virtualWrite(V0, t);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print(t, 1);
  lcd.print(" C");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");
}

// Display Humidity
void displayHumidity() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("DHT sensor error (Humidity)");
    lcd.setCursor(0,0);
    lcd.print("Humidity err");
    return;
  }

  Blynk.virtualWrite(V1, h);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.setCursor(0,1);
  lcd.print(h, 1);
  lcd.print(" %");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

// Display Rain Status
void displayRainStatus() {
  int Rvalue = analogRead(Rain);
  Rvalue = map(Rvalue, 0, 4095, 0, 100);
  Rvalue = (Rvalue - 100) * -1;

  Blynk.virtualWrite(V2, Rvalue);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rain Status:");
  lcd.setCursor(0, 1);
  if (Rvalue > 30) {
    lcd.print("Raining");
  } else {
    lcd.print("Sunny");
  }

  Serial.print("Rain Sensor Value: ");
  Serial.println(Rvalue);
}

// Display Pressure
void displayPressure() {
  status = bmp.startTemperature();
  if (status != 0) {
    delay(status);
    status = bmp.getTemperature(T);

    status = bmp.startPressure(3);
    if (status != 0) {
      delay(status);
      status = bmp.getPressure(P, T);
    }
  }

  Blynk.virtualWrite(V3, P);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressure:");
  lcd.setCursor(0, 1);
  lcd.print(P, 2);
  lcd.print(" Pa");

  Serial.print("Pressure: ");
  Serial.print(P);
  Serial.println(" Pa");
}

void loop() {
  Blynk.run();

  switch (displayStep) {
    case 0: displayTemperature(); break;
    case 1: displayHumidity(); break;
    case 2: displayRainStatus(); break;
    case 3: displayPressure(); break;
  }

  displayStep++;
  if (displayStep > 3) displayStep = 0;

  delay(500); // Update every 0.5 seconds
}
