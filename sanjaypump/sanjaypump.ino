const int relayPin = 4; // GPIO pin connected to relay control pin

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Turn the pump ON
 

  // Turn the pump OFF
  digitalWrite(relayPin, LOW);
  delay(2000); // Wait for 5 seconds before running the pump again
 digitalWrite(relayPin, HIGH);
  delay(2000); // Run the pump for 5 seconds
}
