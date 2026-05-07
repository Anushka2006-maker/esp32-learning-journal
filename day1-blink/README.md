# Day 1: LED Blink

## What I Learned
- **GPIO (General Purpose Input/Output)** – Configuring pins as OUTPUT
- **digitalWrite()** – Setting a pin HIGH (3.3V) or LOW (0V)
- **delay()** – Making the program wait for a specified time in milliseconds

## My Code
```cpp
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
