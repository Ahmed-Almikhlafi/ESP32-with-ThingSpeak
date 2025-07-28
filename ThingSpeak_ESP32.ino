#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiClient client;

// Replace with your ThingSpeak credentials
unsigned long channelID = YOUR_CHANNEL_ID;  // Example: 1234567
const char* writeAPIKey = "YOUR_API_KEY";   // Example: ABCDEFG1234567

const int lightSensorPin = 34;  // GPIO for analog (ESP32) or A0 on ESP8266

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}

void loop() {
  int lightLevel = analogRead(lightSensorPin);
  Serial.println("Light: " + String(lightLevel));

  ThingSpeak.setField(1, lightLevel);
  int result = ThingSpeak.writeFields(channelID, writeAPIKey);

  if(result == 200){
    Serial.println("Data sent successfully!");
  } else {
    Serial.println("Failed to send data. Code: " + String(result));
  }

  delay(15000);  // ThingSpeak limit: 1 update every 15 seconds
}
