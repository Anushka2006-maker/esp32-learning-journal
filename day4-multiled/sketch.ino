// Day 4: Multiple LEDs - Knight Rider Effect

// Step 1: Store all LED pins in an array
int ledPins[] = {13, 12, 14, 27, 26};
int numLeds = 5;  // Number of LEDs

void setup() {
  // Configure all LED pins as OUTPUT
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Pattern 1: LEDs light up one by one (forward)
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);  // Turn ON current LED
    delay(100);                       // Wait 0.1 second
    digitalWrite(ledPins[i], LOW);   // Turn OFF current LED
  }
  
  // Pattern 2: LEDs light up one by one (backward)
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  }
}
