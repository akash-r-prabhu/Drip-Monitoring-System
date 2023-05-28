#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
 
const char* ssid = "akash";
const char* password = "hehehehe";
const char* server = "http://192.168.43.201:8001/getdata";
const int buzzerPin = 15;
 
void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      float cm = doc[0]["cm"];
      if (cm > 14.0) {
        digitalWrite(buzzerPin, HIGH);
        delay(5000);
        digitalWrite(buzzerPin, LOW);
        delay(5000);
      }
      Serial.print("cm: ");
      Serial.println(cm);
    }
    http.end();
  }
  delay(1000);
}
