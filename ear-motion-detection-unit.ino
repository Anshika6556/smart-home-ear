/*
 * EAR Motion Detection Unit (ESP32)
 *
 * Hardware:
 * - ESP32
 * - PIR Motion Sensor (HC-SR501)
 * - Buzzer (GPIO 25)
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ===== CONFIGURATION - UPDATE THESE =====
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* API_ENDPOINT = "https://ufwrwyxhasbdtbekuprl.supabase.co/functions/v1/ingest-event";
const char* DEVICE_ID = "9c04c8dd-8374-4bdd-8dad-1a25b7478798"; // Get from dashboard

// ===== PIN CONFIGURATION =====
const int PIR_PIN = 14;      // PIR sensor output
const int BUZZER_PIN = 25;   // Buzzer

// ===== GLOBAL STATE =====
bool motionActive = false;
unsigned long lastMotionTime = 0;
const unsigned long MOTION_TIMEOUT = 5000; // 5 seconds of no motion to clear
const unsigned long EVENT_COOLDOWN = 2000; // 2 seconds between events
unsigned long lastEventTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("
=== EAR Motion Detection Unit ===");
  connectToWiFi();

  Serial.println("Motion detection unit ready.");
  Serial.println("Waiting for PIR sensor to stabilize (30s)...");
  delay(30000);
  Serial.println("PIR sensor ready!");
}

void loop() {
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    lastMotionTime = millis();

    if (!motionActive) {
      motionActive = true;
      beepShort();
      sendMotionEvent(true);
      Serial.println("Motion DETECTED");
    }
  } else {
    if (motionActive && (millis() - lastMotionTime > MOTION_TIMEOUT)) {
      motionActive = false;
      stopBuzzer();
      sendMotionEvent(false);
      Serial.println("Motion CLEARED");
    }
  }

  delay(100);
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("
WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendMotionEvent(bool detected) {
  if (millis() - lastEventTime < EVENT_COOLDOWN) return;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    connectToWiFi();
    return;
  }

  HTTPClient http;
  http.begin(API_ENDPOINT);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<512> doc;
  doc["device_id"] = DEVICE_ID;
  doc["event_kind"] = "motion";
  doc["label"] = detected ? "Motion detected" : "Motion cleared";
  doc["level"] = detected ? "suspicious" : "safe";
  doc["message"] = detected
    ? "Motion was detected. I'm watching for confirmation from sound signals."
    : "Motion has stopped. I'm continuing silent monitoring.";

  String payload;
  serializeJson(doc, payload);

  Serial.println("
--- Sending Event ---");
  Serial.println(payload);

  int httpCode = http.POST(payload);
  if (httpCode > 0) {
    Serial.printf("[HTTP] Response code: %d
", httpCode);
    Serial.println(http.getString());
    if (httpCode == 201) {
      lastEventTime = millis();
    }
  } else {
    Serial.printf("[HTTP] POST failed: %s
", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void beepShort() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
}

void stopBuzzer() {
  digitalWrite(BUZZER_PIN, LOW);
}
