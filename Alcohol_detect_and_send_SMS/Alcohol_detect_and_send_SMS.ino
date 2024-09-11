#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>

// Define pins
#define ALCOHOL_SENSOR_PIN 2
#define LOAD_PIN 3
#define BUZZER_PIN 4

float lat, lng;

// Phone number to send SMS
const char phoneNumber[] = "+8801314937329";

// Create instances
SoftwareSerial gsm(10, 11); // RX, TX for GSM
SoftwareSerial gps(8, 7); // RX, TX for GPS
LiquidCrystal_I2C lcd(0x27, 16, 2);
TinyGPSPlus gpsData; // Create GPS object

// Variables
bool alcoholDetected = false;

void setup() {
  // Initialize serial communications
  Serial.begin(9600);
  gsm.begin(9600);
  gps.begin(9600);

  // Initialize pins
  pinMode(ALCOHOL_SENSOR_PIN, INPUT);
  pinMode(LOAD_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Set load and buzzer off initially
  digitalWrite(LOAD_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // GSM initialization
  Serial.println("Initializing GSM...");
  delay(1000);
  sendGSMCommand("AT");
  sendGSMCommand("AT+CMGF=1"); // Set SMS mode to text
}

void loop() {
  // Read GPS data
  while (gps.available() > 0) {
    gpsData.encode(gps.read());
  }

  // Check if GPS location is valid
  if (gpsData.location.isValid()) {
    lat = gpsData.location.lat();
    lng = gpsData.location.lng();
  } else {
    Serial.println("Using default location");
    lat = 23.8770388;  // Default latitude
    lng = 90.3202692;  // Default longitude
  }

  // Check alcohol sensor
  alcoholDetected = !digitalRead(ALCOHOL_SENSOR_PIN); // Change logic here

  if (alcoholDetected) {
    sendSMS();

    // Alcohol detected, disable load, sound buzzer, and show warning
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LOAD_PIN, LOW);
    lcd.clear();
    lcd.print("Alcohol Detected!");
    lcd.setCursor(0, 1);
    lcd.print("System off (5)");
    delay(5000); // Wait for 5 seconds

    // Keep system off until reset
    while (1) {
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LOAD_PIN, LOW);
      lcd.clear();
      lcd.print("System off");
      delay(1000); // Add a delay to prevent overwhelming the LCD
    }
  } else {
    // No alcohol detected
    digitalWrite(LOAD_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.clear();
    lcd.print("System Normal");
    lcd.setCursor(0, 1);
    lcd.print("No Alcohol");
  }

  delay(1000);
}

void sendSMS() {
  const char phoneNumber[] = "+8801314937329";

  // Debugging: print to serial monitor
  Serial.println("Sending SMS...");

  // Send SMS with location link
  sendGSMCommand("AT+CMGF=1"); // Set SMS mode to text
  sendGSMCommand(String("AT+CMGS=\"") + phoneNumber + "\"");
  delay(100);
  gsm.print("Alcohol detected! Location: http://maps.google.com/maps?q=");
  gsm.print(lat);
  gsm.print(",");
  gsm.print(lng);
  delay(100);
  gsm.write(26); // ASCII code for Ctrl+Z to send the SMS
  delay(5000); // Wait longer to ensure SMS is sent

  // Debugging: confirm SMS sent
  Serial.println("SMS sent.");
}

void sendGSMCommand(String command) {
  gsm.println(command);
  delay(1000);
  while (gsm.available()) {
    Serial.write(gsm.read()); // Print GSM module response to serial monitor
  }
}
