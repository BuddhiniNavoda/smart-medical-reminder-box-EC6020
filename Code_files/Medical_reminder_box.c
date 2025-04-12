#include <WiFi.h>  
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include "time.h"

// Wi-Fi Credentials (Replace with your actual Wi-Fi name and password)
const char* ssid = "Dinush's iPhone 11";
const char* password = "88888888";

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo & Button Pins
#define SERVO1_PIN 18
#define SERVO2_PIN 19
#define BUTTON_PIN 15  

// LED Pins
#define LED1_PIN 5   // LED for Servo1
#define LED2_PIN 4   // LED for Servo2

// Magnetic Sensor Pins
#define MAG_SENSOR1_PIN 25
#define MAG_SENSOR2_PIN 26
#define MAG_SENSOR3_PIN 27

Servo servo1, servo2;
bool toggle = false;
int setHour = 8, setMinute = 45; 
int selectedBox = 1;

const char* ntpServer = "pool.ntp.org";
long gmtOffset_sec = 19800; 
int daylightOffset_sec = 0;

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Connecting WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected to WiFi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");

    pinMode(BUTTON_PIN, INPUT_PULLUP); 
    pinMode(MAG_SENSOR1_PIN, INPUT_PULLUP);
    pinMode(MAG_SENSOR2_PIN, INPUT_PULLUP);
    pinMode(MAG_SENSOR3_PIN, INPUT_PULLUP);
    
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);

    pinMode(LED1_PIN, OUTPUT); // Set LED1 as output
    pinMode(LED2_PIN, OUTPUT); // Set LED2 as output
    digitalWrite(LED1_PIN, LOW); // Keep LEDs OFF initially
    digitalWrite(LED2_PIN, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Syncing Time...");

    // Sync Time from NTP Server
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.println("Time synchronized!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Medicine Box");
    lcd.setCursor(0, 1);
    lcd.print("System Ready");

    // Set initial servo positions (Closed)
    servo1.write(0);
    servo2.write(0);
}

void loop() {
    checkMagneticSensors();
    checkTimeToOpen();

    if (digitalRead(BUTTON_PIN) == LOW) {
        delay(200); 
        if (toggle) {
            openDoor(servo1, LED1_PIN, "Door 1");
        } else {
            openDoor(servo2, LED2_PIN, "Door 2");
        }
        toggle = !toggle;
    }
}

// Open Door Function with LED Indicator
void openDoor(Servo &servo, int ledPin, const char *doorName) {
    digitalWrite(ledPin, HIGH); // Turn LED ON
    servo.write(90);  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(doorName);
    lcd.setCursor(0, 1);
    lcd.print("Opening...");
    delay(3000);  

    servo.write(0);   
    digitalWrite(ledPin, LOW); // Turn LED OFF
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(doorName);
    lcd.setCursor(0, 1);
    lcd.print("Closed");
    delay(1000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Press Button");
}

void checkMagneticSensors() {
    bool door1Closed = digitalRead(MAG_SENSOR1_PIN);
    bool door2Closed = digitalRead(MAG_SENSOR2_PIN);
    bool door3Closed = digitalRead(MAG_SENSOR3_PIN);
    
    if (!door1Closed || !door2Closed || !door3Closed) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Warning!");
        lcd.setCursor(0, 1);
        lcd.print("Door Open");
        delay(500);
    }
}

void checkTimeToOpen() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    if (timeinfo.tm_hour == setHour && timeinfo.tm_min == setMinute) {
        if (selectedBox == 1) {
            openDoor(servo1, LED1_PIN, "Door 1");
        } else {
            openDoor(servo2, LED2_PIN, "Door 2");
        }
        delay(60000);
    }
}
