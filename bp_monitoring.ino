#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MAX30100_PulseOximeter.h"
#include <ESP8266WiFi.h>

// ---------------- LCD ----------------
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// ---------------- DS18B20 ----------------
#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

// ---------------- MPX5100DP (Blood Pressure) ----------------
#define PRESSURE_PIN A0   // MPX5100DP analog pin
float pressureVoltage, pressure_kPa, mmHg;

// ---------------- MAX30100 ----------------
PulseOximeter pox;
uint32_t tsLastReport = 0;

// ---------------- ESP-01 WiFi + ThingSpeak ----------------
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* host = "api.thingspeak.com";
String apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

// ---------------- Setup ----------------
void onBeatDetected() {
  Serial.println("Beat detected!");
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Temperature sensor
  tempSensor.begin();

  // MAX30100
  if (!pox.begin()) {
    Serial.println("FAILED to initialize MAX30100");
    for(;;);
  } else {
    Serial.println("MAX30100 initialized");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");
}

// ---------------- Loop ----------------
void loop() {
  // ---- Temperature ----
  tempSensor.requestTemperatures();
  float bodyTemp = tempSensor.getTempCByIndex(0);

  // ---- Blood Pressure ----
  pressureVoltage = analogRead(PRESSURE_PIN) * (5.0 / 1023.0);
  pressure_kPa = (pressureVoltage - 0.2) * (100.0 / 4.7); // MPX5100DP transfer function
  mmHg = pressure_kPa * 7.50062;  // Convert kPa to mmHg

  // For demo: Approx systolic & diastolic extraction
  float systolic = mmHg * 0.6; 
  float diastolic = mmHg * 0.4;

  // ---- SpO2 & Heart Rate ----
  pox.update();
  float heartRate = pox.getHeartRate();
  float spo2 = pox.getSpO2();

  // ---- Display on LCD ----
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BP:");
  lcd.print((int)systolic);
  lcd.print("/");
  lcd.print((int)diastolic);

  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(bodyTemp,1);
  lcd.print("C S:");
  lcd.print((int)spo2);

  // ---- Send to ThingSpeak ----
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    if (client.connect(host, 80)) {
      String url = "/update?api_key=" + apiKey +
                   "&field1=" + String(systolic) +
                   "&field2=" + String(diastolic) +
                   "&field3=" + String(bodyTemp) +
                   "&field4=" + String(spo2) +
                   "&field5=" + String(heartRate);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
    }
    client.stop();
  }

  delay(2000); // Update every 2s
}
