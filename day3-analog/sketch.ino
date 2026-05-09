// Day 3: Dimmable LED using Potentiometer
const int LED_PIN = 2;    // LED on GPIO2
const int POT_PIN = 34;   // Potentiometer on GPIO34 (Analog input)

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
