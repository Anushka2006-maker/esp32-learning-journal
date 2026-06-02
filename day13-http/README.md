# Day 13: HTTP Requests – ESP32 Talks to Internet

## What I Learned

### HTTP GET
Request data from a server:
```cpp
HTTPClient http;
http.begin(url);
int code = http.GET();
String response = http.getString();
http.end();
