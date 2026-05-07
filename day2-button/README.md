# Day 2: Button Controlled LED

## What I Learned
- digitalRead() – Reading input from a pin
- INPUT_PULLUP – Internal pull-up resistor
- Serial Monitor – Debugging output
- if/else logic

## My Code
`
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
`

## Simulation Link
(https://wokwi.com/projects/463340774955854849)
