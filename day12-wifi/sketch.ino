// Day 12: Wi-Fi Connection - Connect ESP32 to Internet

#include <WiFi.h>

// ============ WI-FI CREDENTIALS ============
// Replace with your network credentials
const char* ssid = "Wokwi-GUEST";     // Wokwi's simulated Wi-Fi
const char* password = "";             // No password for Wokwi-GUEST

// ============ VARIABLES ============
unsigned long connectionStartTime = 0;
bool connectionAttemptStarted = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("   📶 ESP32 WI-FI CONNECTION DEMO 📶");
  Serial.println("========================================");
  Serial.println();
  
  // Print ESP32 MAC address (unique identifier)
  Serial.print("📇 ESP32 MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println();
  
  // Start Wi-Fi connection
  connectToWiFi();
}

void loop() {
  // Check connection status every second
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 1000) {
    lastCheck = millis();
    
    if (WiFi.status() == WL_CONNECTED) {
      // Print connection info periodically
      static int counter = 0;
      counter++;
      if (counter >= 10) {  // Every 10 seconds
        counter = 0;
        printConnectionInfo();
      }
    } else {
      Serial.println("⚠️ Wi-Fi disconnected! Reconnecting...");
      connectToWiFi();
    }
  }
  
  delay(100);
}

// ============ CONNECT TO WI-FI ============
void connectToWiFi() {
  Serial.print("📡 Connecting to Wi-Fi: ");
  Serial.println(ssid);
  
  // Start connection
  WiFi.begin(ssid, password);
  
  // Wait for connection (with timeout)
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("✅ Wi-Fi connected successfully!");
    printConnectionInfo();
  } else {
    Serial.println();
    Serial.println("❌ Wi-Fi connection failed!");
    Serial.println("   Check SSID and password");
  }
}

// ============ PRINT CONNECTION INFO ============
void printConnectionInfo() {
  Serial.println();
  Serial.println("========== WI-FI CONNECTION INFO ==========");
  Serial.print("📶 SSID: ");
  Serial.println(WiFi.SSID());
  
  Serial.print("🌐 IP Address: ");
  Serial.println(WiFi.localIP());
  
  Serial.print("🎚️ Signal Strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  
  Serial.print("🔗 MAC Address: ");
  Serial.println(WiFi.macAddress());
  
  Serial.print("📡 Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  
  Serial.print("🌍 DNS IP: ");
  Serial.println(WiFi.dnsIP());
  Serial.println("==========================================");
  Serial.println();
}
