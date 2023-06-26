#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int id;
    float cm;
    float inch;
} struct_message;
const char* ssid = "akash";    // Your Wi-Fi network name (SSID)
const char* password = "hehehehe"; // Your Wi-Fi network password
const int buzzerPin = 15; // Replace with the pin number connected to your LED
int buzzerState = LOW;

const char* serverAddress = "http://192.168.43.201:8001/data"; // Server address with the data endpoint

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Device id: ");
  Serial.println(myData.id);
  Serial.print("cm: ");
  Serial.println(myData.cm);
  Serial.print("inch: ");
  Serial.println(myData.inch);
  Serial.println();

  if(myData.id==1){
    if (myData.cm > 14.0) {
      Serial.print("Device id " + String(myData.id) + " has Low volume");
  if(myData.id==1){
  digitalWrite(15, HIGH);
  delay(1000*5);                       // wait for a second
  digitalWrite(15, LOW);    // turn the LED off by making the voltage LOW
      
    }
    else{
  digitalWrite(15, LOW); digitalWrite(4, LOW);
  
}
  }

  }
    if(myData.id==2){
    if (myData.cm > 14.0) {
      Serial.print("Device id " + String(myData.id) + " has Low volume");
  if(myData.id==1){
  digitalWrite(4, HIGH);
  delay(1000*5);                       // wait for a second
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
      
    }
    else{
  digitalWrite(4, LOW); digitalWrite(4, LOW);
  
}
  }
    }
  

 

  
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
   pinMode(15, OUTPUT);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
