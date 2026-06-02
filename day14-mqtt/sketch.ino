// Day 14: MQTT Protocol - Publish and Subscribe

#include <WiFi.h>
#include <PubSubClient.h>

// ============ WI-FI CREDENTIALS ============
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ============ MQTT BROKER SETTINGS ============
// Free public MQTT broker for testing
const char* mqtt_server = "broker.emqx.io";  // Public broker
const int mqtt_port = 1883;                   // Default MQTT port

// ============ TOPICS ============
const char* publish_topic = "esp32/sensor/temperature";
const char* subscribe_topic = "esp32/command";

// ============ GLOBAL OBJECTS ============
WiFiClient espClient;
PubSubClient client(espClient);

// ============ SENSOR SIMULATION ============
float simulatedTemperature = 25.0;
unsigned long lastPublishTime = 0;
unsigned long lastReconnectAttempt = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("   📡 MQTT PROTOCOL DEMO 📡");
  Serial.println("========================================");
  Serial.println();
  
  // Connect to Wi-Fi
  connectToWiFi();
  
  // Configure MQTT server
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
  
  Serial.println("========================================");
  Serial.println("MQTT Broker: broker.emqx.io");
  Serial.println("Port: 1883");
  Serial.println();
  Serial.println("You can use MQTT Explorer or MQTT app");
  Serial.println("to subscribe to topics and test!");
  Serial.println("========================================");
  Serial.println();
}

void loop() {
  // Ensure MQTT connection is active
  if (!client.connected()) {
    reconnectMQTT();
  }
  
  client.loop();  // Process incoming messages
  
  // Publish temperature every 5 seconds
  if (millis() - lastPublishTime > 5000) {
    lastPublishTime = millis();
    publishTemperature();
  }
}

// ============ CONNECT TO WI-FI ============
void connectToWiFi() {
  Serial.print("📡 Connecting to Wi-Fi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("✅ Wi-Fi connected!");
    Serial.print("📶 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("❌ Wi-Fi connection failed!");
    while(1);
  }
  Serial.println();
}

// ============ MQTT CALLBACK (Receives Messages) ============
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.println();
  Serial.println("📨 MESSAGE RECEIVED!");
  Serial.print("   Topic: ");
  Serial.println(topic);
  
  // Convert payload to string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("   Message: ");
  Serial.println(message);
  
  // Process commands
  if (String(topic) == subscribe_topic) {
    if (message == "STATUS") {
      Serial.println("   → Sending status update...");
      publishStatus();
    } 
    else if (message == "RESET") {
      Serial.println("   → Simulating reset...");
      simulatedTemperature = 25.0;
      publishTemperature();
    }
    else if (message.startsWith("SET_TEMP:")) {
      // Parse temperature command: SET_TEMP:30.5
      int colonIndex = message.indexOf(':');
      if (colonIndex != -1) {
        float newTemp = message.substring(colonIndex + 1).toFloat();
        simulatedTemperature = newTemp;
        Serial.print("   → Temperature set to: ");
        Serial.println(simulatedTemperature);
        publishTemperature();
      }
    }
    else {
      Serial.print("   → Unknown command: ");
      Serial.println(message);
    }
  }
  
  Serial.println();
}

// ============ RECONNECT TO MQTT BROKER ============
void reconnectMQTT() {
  // Try to reconnect every 5 seconds
  if (millis() - lastReconnectAttempt < 5000) {
    return;
  }
  lastReconnectAttempt = millis();
  
  Serial.print("🔌 Connecting to MQTT broker...");
  
  // Generate unique client ID
  String clientId = "ESP32Client-";
  clientId += String(random(0xffff), HEX);
  
  if (client.connect(clientId.c_str())) {
    Serial.println(" ✅ Connected!");
    
    // Subscribe to command topic
    if (client.subscribe(subscribe_topic)) {
      Serial.print("   📝 Subscribed to: ");
      Serial.println(subscribe_topic);
    }
    
    // Publish connected message
    client.publish(publish_topic, "ESP32 connected to MQTT!");
    publishStatus();
    
  } else {
    Serial.print(" ❌ Failed, rc=");
    Serial.println(client.state());
  }
}

// ============ PUBLISH TEMPERATURE READING ============
void publishTemperature() {
  // Simulate temperature changing
  simulatedTemperature += random(-10, 15) / 10.0;
  if (simulatedTemperature > 45) simulatedTemperature = 45;
  if (simulatedTemperature < 15) simulatedTemperature = 15;
  
  // Create JSON message
  String jsonPayload = "{";
  jsonPayload += "\"temperature\": ";
  jsonPayload += simulatedTemperature;
  jsonPayload += ",\"unit\": \"C\"";
  jsonPayload += ",\"timestamp\": ";
  jsonPayload += millis() / 1000;
  jsonPayload += "}";
  
  // Publish to topic
  if (client.publish(publish_topic, jsonPayload.c_str())) {
    Serial.print("📤 Published to [");
    Serial.print(publish_topic);
    Serial.print("]: ");
    Serial.println(jsonPayload);
  } else {
    Serial.println("❌ Publish failed!");
  }
}

// ============ PUBLISH STATUS UPDATE ============
void publishStatus() {
  String statusMsg = "{";
  statusMsg += "\"status\": \"online\",";
  statusMsg += "\"temperature\": ";
  statusMsg += simulatedTemperature;
  statusMsg += ",\"uptime\": ";
  statusMsg += millis() / 1000;
  statusMsg += "}";
  
  client.publish("esp32/status", statusMsg.c_str());
  Serial.println("📤 Status published!");
}
