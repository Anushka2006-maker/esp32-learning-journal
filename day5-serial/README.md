# Day 5: Serial Commands - Keyboard Control

## What I Learned

### New Functions
- `Serial.available()` – Check if data received
- `Serial.readString()` – Read text input
- `.trim()` – Remove spaces/newlines
- `.toUpperCase()` – Convert to uppercase
 SIMULATION
https://wokwi.com/projects/463731977478864897

## My Code
```cpp
const int LED_PIN = 2;
String command;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.readString();
    command.trim();
    command.toUpperCase();
    
    if (command == "ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
    }
    else if (command == "OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
    }
    else if (command == "BLINK") {
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(300);
        digitalWrite(LED_PIN, LOW);
        delay(300);
      }
      Serial.println("Blinked!");
    }
  }
}
