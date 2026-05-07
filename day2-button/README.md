# Day 2: Button Controlled LED

## What I Learned
- **digitalRead()** – Reading the state of an input pin (HIGH or LOW)
- **INPUT_PULLUP** – Enabling internal pull-up resistor (no external resistor needed)
- **Serial Monitor** – Debugging and seeing output from ESP32
- **if/else logic** – Making decisions based on input

## Key Insight
With pull-up resistors, **pressed button = LOW (0)**, not HIGH (1)

## My Code
```cpp
const int LED_PIN = 2;
const int BUTTON_PIN = 4;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
  }
  delay(100);
}
