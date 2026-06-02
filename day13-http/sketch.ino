// Day 13: HTTP GET Request - Get Data from Internet

#include <WiFi.h>
#include <HTTPClient.h>

// ============ WI-FI CREDENTIALS ============
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ============ FREE APIs FOR TESTING ============
// These are public test APIs - no API key needed!

// API 1: Get current time
const char* timeAPI = "http://worldtimeapi.org/api/timezone/Asia/Kolkata";

// API 2: Get random facts
const char* factAPI = "https://uselessfacts.jsph.pl/api/v2/facts/random";

// API 3: Get IP address
const char* ipAPI = "https://api.ipify.org?format=json";

// API 4: Test endpoint
const char* testAPI = "https://jsonplaceholder.typicode.com/posts/1";

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("   🌐 ESP32 HTTP GET REQUESTS 🌐");
  Serial.println("========================================");
  Serial.println();
  
  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() {
  Serial.println("========================================");
  Serial.println("Fetching data from the internet...");
  Serial.println();
  
  // 1. Get current time from WorldTimeAPI
  getCurrentTime();
  delay(2000);
  
  // 2. Get random fact
  getRandomFact();
  delay(2000);
  
  // 3. Get IP address
  getMyIP();
  delay(2000);
  
  // 4. Get test data
  getTestData();
  
  Serial.println();
  Serial.println("Waiting 30 seconds before next fetch...");
  Serial.println("========================================");
  Serial.println();
  
  delay(30000);
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

// ============ HTTP GET REQUEST FUNCTIONS ============

// Function 1: Get current time
void getCurrentTime() {
  Serial.println("--- GETTING CURRENT TIME ---");
  
  HTTPClient http;
  http.begin(timeAPI);
  
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("✅ Response received!");
      Serial.println("Raw response:");
      Serial.println(payload);
      Serial.println();
      
      // Parse datetime from response
      int datetimeIndex = payload.indexOf("\"datetime\":\"");
      if (datetimeIndex != -1) {
        String datetime = payload.substring(datetimeIndex + 12, datetimeIndex + 31);
        Serial.print("🕐 Current Time: ");
        Serial.println(datetime);
      }
      
      // Parse timezone
      int timezoneIndex = payload.indexOf("\"timezone\":\"");
      if (timezoneIndex != -1) {
        String timezone = payload.substring(timezoneIndex + 12, payload.indexOf("\"", timezoneIndex + 12));
        Serial.print("📍 Timezone: ");
        Serial.println(timezone);
      }
    }
  } else {
    Serial.print("❌ HTTP request failed, error: ");
    Serial.println(http.errorToString(httpCode));
  }
  
  http.end();
  Serial.println();
}

// Function 2: Get random fact
void getRandomFact() {
  Serial.println("--- GETTING RANDOM FACT ---");
  
  HTTPClient http;
  http.begin(factAPI);
  
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("✅ Response received!");
      
      // Parse the fact from JSON
      int factStart = payload.indexOf("\"text\":\"");
      if (factStart != -1) {
        int factEnd = payload.indexOf("\"", factStart + 8);
        String fact = payload.substring(factStart + 8, factEnd);
        
        // Handle escaped characters
        fact.replace("\\\"", "\"");
        fact.replace("\\n", " ");
        
        Serial.println("💡 Random Fact:");
        Serial.println(fact);
      }
    }
  } else {
    Serial.print("❌ HTTP request failed, error: ");
    Serial.println(http.errorToString(httpCode));
  }
  
  http.end();
  Serial.println();
}

// Function 3: Get your public IP address
void getMyIP() {
  Serial.println("--- GETTING PUBLIC IP ADDRESS ---");
  
  HTTPClient http;
  http.begin(ipAPI);
  
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("✅ Response received!");
      
      // Parse IP from JSON
      int ipStart = payload.indexOf("\"ip\":\"");
      if (ipStart != -1) {
        int ipEnd = payload.indexOf("\"", ipStart + 6);
        String ip = payload.substring(ipStart + 6, ipEnd);
        Serial.print("🌐 Your Public IP: ");
        Serial.println(ip);
      }
    }
  } else {
    Serial.print("❌ HTTP request failed, error: ");
    Serial.println(http.errorToString(httpCode));
  }
  
  http.end();
  Serial.println();
}

// Function 4: Get test data
void getTestData() {
  Serial.println("--- GETTING TEST DATA ---");
  
  HTTPClient http;
  http.begin(testAPI);
  
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("✅ Response received!");
      
      // Parse JSON fields
      int userIdStart = payload.indexOf("\"userId\":");
      if (userIdStart != -1) {
        int userIdEnd = payload.indexOf(",", userIdStart);
        String userId = payload.substring(userIdStart + 9, userIdEnd);
        Serial.print("👤 User ID: ");
        Serial.println(userId);
      }
      
      int idStart = payload.indexOf("\"id\":");
      if (idStart != -1) {
        int idEnd = payload.indexOf(",", idStart);
        String id = payload.substring(idStart + 5, idEnd);
        Serial.print("📝 ID: ");
        Serial.println(id);
      }
      
      int titleStart = payload.indexOf("\"title\":\"");
      if (titleStart != -1) {
        int titleEnd = payload.indexOf("\"", titleStart + 9);
        String title = payload.substring(titleStart + 9, titleEnd);
        Serial.print("📌 Title: ");
        Serial.println(title);
      }
    }
  } else {
    Serial.print("❌ HTTP request failed, error: ");
    Serial.println(http.errorToString(httpCode));
  }
  
  http.end();
  Serial.println();
}
