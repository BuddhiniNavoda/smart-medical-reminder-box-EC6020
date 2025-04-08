#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include "time.h"
#include "BluetoothSerial.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
BluetoothSerial SerialBT;

const char* ssid = "Dinush's iPhone 11";  
const char* password = "88888888"; 

#define SERVO1_PIN 18
#define SERVO2_PIN 19
#define BUTTON_PIN 15
#define LED1_PIN 5
#define LED2_PIN 4
#define MAG_SENSOR1_PIN 25
#define MAG_SENSOR2_PIN 26

Servo servo1, servo2;

const char* ntpServer = "pool.ntp.org";
long gmtOffset_sec = 19800;
int daylightOffset_sec = 0;

int door1Slots[5][2];
int door2Slots[5][2];
int door1Count = 0;
int door2Count = 0;

bool manualToggle = false;
bool doorsAreOpen = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-MedBox");

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Bluetooth Ready");

  WiFi.begin(ssid, password);
  lcd.setCursor(0, 1);
  lcd.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MAG_SENSOR1_PIN, INPUT_PULLUP);
  pinMode(MAG_SENSOR2_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo1.write(0);
  servo2.write(0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(2000);
}

void loop() {
  checkBluetoothCommands();
  checkTimeToOpen();
  updateDisplay();
  checkMagneticSensors();
  checkManualButton();
}

void openDoor(int door) {
  if (door == 1) {
    servo1.write(90);
    digitalWrite(LED1_PIN, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door 1 Opened");
  } else if (door == 2) {
    servo2.write(90);
    digitalWrite(LED2_PIN, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door 2 Opened");
  }
  delay(30000); // Wait 30 seconds
  closeDoors();
}

void openBothDoors() {
  servo1.write(90);
  servo2.write(90);
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  doorsAreOpen = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Both Doors Open");
}

void closeDoors() {
  servo1.write(0);
  servo2.write(0);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  doorsAreOpen = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Doors Closed");
  delay(2000);
}

void checkManualButton() {
  static bool lastButtonState = HIGH;
  bool currentState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentState == LOW) {
    manualToggle = !manualToggle;
    if (manualToggle) openBothDoors();
    else closeDoors();
  }
  lastButtonState = currentState;
}

void checkBluetoothCommands() {
  if (SerialBT.available()) {
    String input = SerialBT.readStringUntil('\n');
    input.trim();

    door1Count = 0;
    door2Count = 0;

    int sepIndex = input.indexOf(';');
    String door1Str = (sepIndex != -1) ? input.substring(0, sepIndex) : input;
    String door2Str = (sepIndex != -1) ? input.substring(sepIndex + 1) : "";

    if (door1Str.startsWith("DOOR1:")) {
      door1Str = door1Str.substring(6);
      door1Count = parseTimeSlots(door1Str, door1Slots, 5);
    }

    if (door2Str.startsWith("DOOR2:")) {
      door2Str = door2Str.substring(6);
      door2Count = parseTimeSlots(door2Str, door2Slots, 5);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Times Updated");
    delay(2000);
  }
}

int parseTimeSlots(String timesStr, int slots[][2], int maxSlots) {
  int count = 0;
  while (count < maxSlots && timesStr.length() > 0) {
    int commaIndex = timesStr.indexOf(',');
    String timeStr = (commaIndex >= 0) ? timesStr.substring(0, commaIndex) : timesStr;

    int colonIndex = timeStr.indexOf(':');
    if (colonIndex > 0) {
      int h = timeStr.substring(0, colonIndex).toInt();
      int m = timeStr.substring(colonIndex + 1).toInt();
      if (h >= 0 && h <= 23 && m >= 0 && m <= 59) {
        slots[count][0] = h;
        slots[count][1] = m;
        count++;
      }
    }

    if (commaIndex >= 0)
      timesStr = timesStr.substring(commaIndex + 1);
    else
      break;
  }
  return count;
}

void checkTimeToOpen() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  for (int i = 0; i < door1Count; i++) {
    if (timeinfo.tm_hour == door1Slots[i][0] && timeinfo.tm_min == door1Slots[i][1]) {
      openDoor(1);
      break;
    }
  }

  for (int i = 0; i < door2Count; i++) {
    if (timeinfo.tm_hour == door2Slots[i][0] && timeinfo.tm_min == door2Slots[i][1]) {
      openDoor(2);
      break;
    }
  }
}

void updateDisplay() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate < 10000) return;
  lastUpdate = millis();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("D1:");
  for (int i = 0; i < door1Count; i++) {
    lcd.print(door1Slots[i][0]);
    lcd.print(":");
    lcd.print(door1Slots[i][1]);
    if (i < door1Count - 1) lcd.print(",");
  }

  lcd.setCursor(0, 1);
  lcd.print("D2:");
  for (int i = 0; i < door2Count; i++) {
    lcd.print(door2Slots[i][0]);
    lcd.print(":");
    lcd.print(door2Slots[i][1]);
    if (i < door2Count - 1) lcd.print(",");
  }
}

void checkMagneticSensors() {
  if (!digitalRead(MAG_SENSOR1_PIN)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door 1 Open!");
    delay(1000);
  }

  if (!digitalRead(MAG_SENSOR2_PIN)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door 2 Open!");
    delay(1000);
  }
}