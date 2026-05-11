# Day 6: DHT22 Temperature & Humidity Sensor

## What I Learned

### New Concepts
- **DHT22 Sensor** – Measures temperature and humidity
- **Libraries** – Reusing pre-written code (`#include <DHT.h>`)
- **Sensor initialization** – `dht.begin()`
- **Reading sensors** – `readTemperature()`, `readHumidity()`
- **Error checking** – `isnan()` to detect failed readings

### Key Insight
Most complex sensors have libraries that handle the low-level communication. You just need to call simple functions!
##Simulation
https://wokwi.com/projects/463732457483540481

## My Code
```cpp
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(2000);
  
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);
  float humidity = dht.readHumidity();
  
  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Sensor read failed!");
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
