# Day 4: Multiple LEDs + Light Patterns (Knight Rider)

## What I Learned

### New Concepts
- **Arrays** – Storing multiple values in one variable
- **For loops** – Repeating code efficiently
- **LED chaser patterns** – Sequential lighting effects

### Key Insight
Arrays + loops = Professional code. Without them, controlling 100 LEDs would take 100 lines of code!
## simulation Link
https://wokwi.com/projects/463555038959684609

## My Code
```cpp
int ledPins[] = {13, 12, 14, 27, 26};
int numLeds = 5;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // My patterns here
}
