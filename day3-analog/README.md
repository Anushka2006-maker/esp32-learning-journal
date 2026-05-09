# Day 3: Analog Input + PWM (Dimmable LED)

## What I Learned

### New Concepts
- **Analog Input** – Reading continuous values (0-4095) using `analogRead()`
- **PWM (Pulse Width Modulation)** – Simulating analog output using `analogWrite()`
- **Potentiometer** – A knob that changes voltage
- **map() function** – Converting between different value ranges

### Key Insight
- Digital = ON/OFF (2 states)
- Analog = Continuous range (4096 states on ESP32)
 ## Simulation Link
 (https://wokwi.com/projects/463554709550526465)

## My Code
```cpp
const int LED_PIN = 2;
const int POT_PIN = 34;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(POT_PIN);
  int brightness = map(sensorValue, 0, 4095, 0, 255);
  analogWrite(LED_PIN, brightness);
  
  Serial.print("Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);
  
  delay(50);
}
