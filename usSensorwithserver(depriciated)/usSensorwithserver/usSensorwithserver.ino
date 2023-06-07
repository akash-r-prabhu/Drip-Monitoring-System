#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "akash";    // Your Wi-Fi network name (SSID)
const char* password = "hehehehe"; // Your Wi-Fi network password

const char* serverAddress = "http://192.168.131.201:8001/data"; // Server address with the data endpoint

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  // Send HTTP GET request to server
  String getRequest = String(serverAddress) + "?distanceCm=" + String(distanceCm) + "&distanceInch=" + String(distanceInch);
  Serial.println(getRequest);
  HTTPClient http;
  http.begin(getRequest);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("HTTP GET request sent, response code: %d\n", httpCode);
  } else {
    Serial.println("HTTP GET request failed");
  }
  http.end();

  delay(1000);
}
