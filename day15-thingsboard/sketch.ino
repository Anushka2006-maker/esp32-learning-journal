// Day 15: ThingsBoard IoT Cloud Dashboard

#include <WiFi.h>
#include <ThingsBoard.h>
#include <DHT.h>

// ============ WI-FI CREDENTIALS ============
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ============ THINGSBOARD CREDENTIALS ============
const char* thingsboard_server = "demo.thingsboard.io";
const char* tb_access_token = "YOUR_ACCESS_TOKEN";  // Get from ThingsBoard

// ============ DHT SENSOR ============
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ============ THINGSBOARD CLIENT ============
WiFiClient wifiClient;
ThingsBoard tb(wifiClient);

// ============ TIMING VARIABLES ============
unsigned long lastPublish = 0;
const unsigned long PUBLISH_INTERVAL = 10000;  // 10 seconds

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("    THINGSBOARD CLOUD DASHBOARD ");
  Serial.println("========================================");
  
  dht.begin();
  connectToWiFi();
  connectToThingsBoard();
}

void connectToWiFi() {
  Serial.print(" Connecting to Wi-Fi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println(" Wi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void connectToThingsBoard() {
  Serial.print(" Connecting to ThingsBoard...");
  
  if (tb.connect(thingsboard_server, tb_access_token)) {
    Serial.println("  Connected!");
    Serial.println(" Dashboard: https://demo.thingsboard.io/dashboard");
  } else {
    Serial.println("  Connection failed!");
    Serial.println("Note: You need to create an access token at demo.thingsboard.io");
  }
}

void loop() {
  if (!tb.connected()) {
    connectToThingsBoard();
  }
  
  tb.loop();
  
  if (millis() - lastPublish > PUBLISH_INTERVAL) {
    lastPublish = millis();
    publishSensorData();
  }
}

void publishSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(" Failed to read DHT sensor!");
    return;
  }
  
  Serial.println();
  Serial.println(" Publishing to ThingsBoard:");
  Serial.print("   Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("   Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  tb.sendTelemetryFloat("temperature", temperature);
  tb.sendTelemetryFloat("humidity", humidity);
  
  Serial.println("Data sent to cloud!");
  Serial.println();
}
