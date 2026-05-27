# Day 12: Wi-Fi Connectivity

## What I Learned

### New Concepts
- **Wi-Fi Station Mode** – ESP32 connects to existing network
- **SSID** – Network name
- **IP Address** – Device address on network
- **RSSI** – Signal strength (closer to 0 = stronger)

### Important Wi-Fi Functions
```cpp
WiFi.begin(ssid, password);     // Connect to network
WiFi.status();                   // Check connection
WiFi.localIP();                  // Get IP address
WiFi.RSSI();                     // Get signal strength
WiFi.scanNetworks();             // Find available networks
