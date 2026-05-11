// Day 6: Temperature and Humidity Sensor (DHT22)

#include <DHT.h>

// Pin Definitions
#define DHTPIN 15      // DHT22 data pin connected to GPIO15
#define DHTTYPE DHT22  // Using DHT22 sensor

// Create DHT object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);  // Wait for sensor to stabilize
  
  Serial.println("=== DHT22 Temperature & Humidity Sensor ===");
  Serial.println("Sensor is starting...");
  
  // Initialize the DHT sensor
  dht.begin();
  
  Serial.println("Ready! Reading sensor data...");
  Serial.println("==========================================");
}

void loop() {
  // Wait 2 seconds between readings (DHT22 needs this)
  delay(2000);
  
  // Read temperature (Celsius)
  float temperatureC = dht.readTemperature();
  
  // Read temperature (Fahrenheit)
  float temperatureF = dht.readTemperature(true);
  
  // Read humidity
  float humidity = dht.readHumidity();
  
  // Check if readings are valid (not NaN - Not a Number)
  if (isnan(temperatureC) || isnan(humidity)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    Serial.println("Check wiring or try again...");
    return;  // Exit this loop iteration, try again later
  }
  
  // Print all readings to Serial Monitor
  Serial.println("=== Current Readings ===");
  Serial.print("🌡️ Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  
  Serial.print("🌡️ Temperature: ");
  Serial.print(temperatureF);
  Serial.println(" °F");
  
  Serial.print("💧 Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println("========================");
}
