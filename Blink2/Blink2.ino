// Author:      vojoel
// Date:        29 Nov 2021
// Description: Program to let two LEDs blink at different rates T3, T6


void setup() {
  pinMode(3, OUTPUT); //Blue LED
  pinMode(6, OUTPUT); //Red LED
}

void loop() {
  blinker(100000, 500000);    // Blink LEDs with periods 0.2s(blue), 1s(red)
}

// PRE: T3, T6 > 0, pins 3 and 6 of Arduino connected to LEDs
// POST: LEDs blink at periods 2*T3(blue), 2*T6(red)
void blinker (unsigned int T3, unsigned int T6){
  static unsigned long last_us_3 = 0;
  static unsigned long last_us_6 = 0;
  // Save current timer value
  unsigned long long curr_ms = micros();
  // Check if half period T3 has already passed. If yes, switch state.
  if ((curr_ms - last_us_3) >= T3){ 
    last_us_3 = curr_ms; 
    digitalWrite(3, !digitalRead(3));
  }
  // Analoguous for second LED
  if ((curr_ms - last_us_6) >= T6){ 
    last_us_6 = curr_ms; 
    digitalWrite(6, !digitalRead(6));
  }
}
