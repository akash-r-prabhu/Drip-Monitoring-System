#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
 
const char* ssid = "akash";
const char* password = "hehehehe";
const char* server = "http://192.168.43.201:8001/getdata";
const int buzzerPin = 15;

#define i2c_addr 0x3c
#define sda_2 19
#define scl_2 18

const unsigned char bridge[] = {
  // Bridge image data
};


TwoWire i2c2 = TwoWire(1);

Adafruit_SH1106G display2 = Adafruit_SH1106G(128, 64, &Wire1, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Wire.begin();
  Wire1.begin(sda_2, scl_2, 100000);
  display2.begin(0x3c, true);
  delay(2000);
  display2.display();
  delay(50);
  

  display2.clearDisplay();
}
void connectToWifi(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  Wire.begin();
  Wire1.begin(sda_2, scl_2, 100000);
  display2.begin(0x3c, true);
  delay(2000);
  display2.display();
  delay(50);
}
void loop() {
  display2.setTextColor(SH110X_WHITE);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      float cm = doc[0]["cm"];
      String dripLevelText = "The current drip level is " + String(100-((cm/17)*100))+" %";
      display2.clearDisplay();
  display2.setCursor(0, 0);
  display2.println(dripLevelText);
  display2.display();
  delay(1000);

      if (cm > 14.0) {
        digitalWrite(buzzerPin, HIGH);
      }
      else{
        digitalWrite(buzzerPin, LOW);
      }
      Serial.print("cm: ");
      Serial.println(cm);
    }
    else{
      display2.clearDisplay();
    }
    http.end();
  }
  else{
    connectToWifi();
  }
  delay(1000);
}
