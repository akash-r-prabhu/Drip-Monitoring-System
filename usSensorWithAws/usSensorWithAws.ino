#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32_DHT11"                         //change this

const char* serverAddress = "http://192.168.43.201:8001/data"; // Server address with the data endpoint
 
const char WIFI_SSID[] = "akash";               //change this
const char WIFI_PASSWORD[] = "hehehehe";           //change this
const char AWS_IOT_ENDPOINT[] = "a1odzakl96xx5h-ats.iot.us-east-1.amazonaws.com";       //change this

 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVALZzHtxm14CO3PZfi32LuJXEC+5BMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA1MjgwNTQy
MTdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDKX3tgkSoGehh80W89
n0ZtR6ZPkJE2pbQWnx8I5tjYm9LW+fdyssF07HF/CAup402bb2qdZFgfSOe9QyxK
fP+uN4SG9LI/BXwl2blrAKpDLy7EXdXI5C8IA0pKENrHVGkDC1EuY9JVDSpOE15+
ewbzTh3hPPwaFHq78Ub2leTZ8cqtGVnWi8tTBmWrIt5gDKlS2Jp7PWloHqCyog7r
lI/9fgMQbrV14CUjxX6noww3P7gtQVrz8xUHJLmSWHk9sNrwiwvSx0mP2bgk6yi/
ZsAHAI7E7xvSQipIPGHCAhNwgrsZk9dMCQha7JRfJjLhWkiTjpRnjxXSfMLjPj7X
Pc8pAgMBAAGjYDBeMB8GA1UdIwQYMBaAFGqQOyRF/39FQZLrPEFsdFBVNs7HMB0G
A1UdDgQWBBSX+/eEwzmdGP6PQvME60a+bRzW5DAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAPePbFAQibnQpbUdQttvRGtRM
wfNhneMabtdjoGJ6swCEzJXGMRZ/ruEToEViparNftupJjPZKoqvHIv1cg7ZV9CV
OBKn+ex84N8xqOxn5QXQaOQDGHSuF2hk5cb1O12kAn8invMGl7+q+RrZR3pbj3UH
/3yicgsxs7eT4ZPRFGgjTU5XICvxqkxs3NaRBF5deHZ2lJ36vrA19+1LWHEbxzjb
9Kx9fvrgDSCerr6K+57fBnVC9TYXYgCgD57/aCI+7F3ipveelxm+N28KCwA+GlMO
wZiHbRb7M+XkcH7DLIzWgXC3kgYVA/InGaRIRGzixVSInF84qeuiUqmqERG19w==
-----END CERTIFICATE-----

 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAyl97YJEqBnoYfNFvPZ9GbUemT5CRNqW0Fp8fCObY2JvS1vn3
crLBdOxxfwgLqeNNm29qnWRYH0jnvUMsSnz/rjeEhvSyPwV8Jdm5awCqQy8uxF3V
yOQvCANKShDax1RpAwtRLmPSVQ0qThNefnsG804d4Tz8GhR6u/FG9pXk2fHKrRlZ
1ovLUwZlqyLeYAypUtiaez1paB6gsqIO65SP/X4DEG61deAlI8V+p6MMNz+4LUFa
8/MVByS5klh5PbDa8IsL0sdJj9m4JOsov2bABwCOxO8b0kIqSDxhwgITcIK7GZPX
TAkIWuyUXyYy4VpIk46UZ48V0nzC4z4+1z3PKQIDAQABAoIBAQCooNE8kRlUlk5r
S1SHI33at1ZUfCEUSRT7uJFyqHDOZWFVMqrHDz52QEL+V+ToJfhX6YoMJj3rq6M2
KI/ybZ/bOnWawrD4JIjjPT3sdHxrSRiOFaZ7I/AwnBU+DDdQ2vw5xidaIWF072ht
8GPPvpH3EQOC2H80+BWhH5ZDCHnOQ9mMTGGVG+fIrh/dyPUFUXaDH5XI7G9srDRQ
rpu2Fbo7/sK2dHrGO4PmJVysGJ0ejA+PEGsLGVHG+RKEcIK+DS3fpw4ckEeKvuuO
4fVhhUQ4h8wUii8F++97uXfa0VCsRqH1VCgnv2xMiUaCPouusIbPz7ZTLj70wRRB
pA3ghyUVAoGBAOO6xHB1vYdFrverV1Ozj+xbbQeVNe5rCc7njNPBV1pGmwcT/YBi
gQnqjPIq7T5/jKwOLHMGTII6MlZYZy8MMz/3yLFAoZ/WhMjfyqs10p9C/8zBSJBG
tiyfSGAf0g9bjdS1I5onLSV0f+HS7luhwy9DVTekeRjLpopTRURjP58nAoGBAON+
4kBkYo2Xu4z6IgndI/IqmOWHf0vN/k7zXIqKnqQcQwywH20jp+O+gCSPP9ZDR6qc
832FRNFdERh2Na4qC/LAvoBgLC26yGjZ1Up+Xexf+4EsuqmtjrsnnDzBcgwIzxYk
p5rjRw9rxx3uLPcdjighUcfk/ZeRLP0cs3bR0hEvAoGAFZUGtu3Bp4dIHLrFTO5w
jmLfw181vEGyrUQuiYcCQ1D7skEHvloXhpwO/Yhp8YlfCJNTTRdkutbPHHXGWaQb
W02dXIcWijJnZS4oY+925ZcQ7RPIT7wT2cjCsDFz0/bGS0lbdWmPEsSmtf0qj86V
0+3arqpMu7fZMbTQlLmfNvMCgYBANvmgWXWkKBdNpPFkvWI/Ih0EdSnOePf2yyTt
ClHbWwrmEvTb9ruWQpijOTg4v8cD9seYP7z8J/wCXqOqZL34qMVdMUhnJBkb15ko
LOFQLousm7aY3J+0Xmrwj14k3Xuu8WvKAat2Q+LxpOBWZKZS14zhEtcuKFF9pNNX
j8RvCwKBgQClgiqabeCnw7n0p+4ldcWtnlT16JAWdZ/hSbKSt0WD4XBrNIckoKMN
MS3ZlsoAwNhi67Vwj7fluRMOsOdLLYsNb5Yb5O9yOIBYadIBa8agD/7JcsAVmOOj
sk0Na1LMTk1RP5vlSgkipw8zLdLr4VxH2pUs+vMp6ljOmeXmxhjBSA==
-----END RSA PRIVATE KEY-----
)KEY";


 

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

 
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
 
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}
 
void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["cm"]=distanceCm;
  doc["Inch"]=distanceInch;
  char jsonBuffer[1024];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}
 
void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  connectAWS();
}
 
void loop()
{
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
 
  publishMessage();
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
  
  client.loop();
  delay(10000);
}
