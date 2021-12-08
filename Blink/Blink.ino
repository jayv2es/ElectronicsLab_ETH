void setup() {
  // Initialize pin 3 as output
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(3, HIGH);  // Turns LED on
  delay(500);             // Waits 0.5s
  digitalWrite(3, LOW);   // Turns LED off
  delay(500);             // Waits 0.5s
}
