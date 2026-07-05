# ESP32 Learning Journal

My 35-day journey learning IoT and Embedded Systems as an ECE student. This repository documents my daily progress, projects, and skills acquired during my summer break.

---

## 📊 Progress Tracker

| Day | Topic | Project | Status | Code |
|-----|-------|---------|--------|------|
| 1 | LED Blink | Blink an LED | ✅ Complete | [View](day1-blink/sketch.ino) |
| 2 | Button Control | Button-controlled LED | ✅ Complete | [View](day2-button/sketch.ino) |
| 3 | Analog Input + PWM | Dimmable LED with Potentiometer | ✅ Complete | [View](day3-analog/sketch.ino) |
| 4 | Multiple LEDs | LED Chaser / Knight Rider | ✅ Complete | [View](day4-multiled/sketch.ino) |
| 5 | Serial Commands | Keyboard-controlled LED | ✅ Complete | [View](day5-serial/sketch.ino) |
| 6 | Sensors | DHT22 Temperature & Humidity | ✅ Complete | [View](day6-sensor/sketch.ino) |
| 7 | LCD Display | 16x2 I2C LCD | ✅ Complete | [View](day7-lcd/sketch.ino) |
| 8 | Dual Displays | LCD + 7-Segment | ✅ Complete | [View](day8-dual-display/sketch.ino) |
| 9 | Interrupts | Instant Button Response | ✅ Complete | [View](day9-interrupts/sketch.ino) |
| 10 | Hardware Timers | Precise Scheduling | ✅ Complete | [View](day10-timers/sketch.ino) |
| 11 | PWM Deep Dive | LEDC, Frequency, Resolution | ✅ Complete | [View](day11-pwm-deep/sketch.ino) |
| 12 | Wi-Fi Connectivity | Internet Connection | ✅ Complete | [View](day12-wifi/sketch.ino) |
| 13 | HTTP Requests | GET & POST to Web Servers | ✅ Complete | [View](day13-http/sketch.ino) |
| 14 | MQTT Protocol | Publish & Subscribe | ✅ Complete | [View](day14-mqtt/sketch.ino) |
| 15 | Cloud Dashboard | ThingsBoard IoT Platform | ✅ Complete | [View](day15-thingsboard/sketch.ino) |

---

## 🎯 Projects Completed

| # | Project | Description | Code | Demo |
|---|---------|-------------|------|------|
| 1 | Smart Pill Reminder Box | Medicine reminder with visual alerts and escalation | [View](project1-pill-reminder/sketch.ino) | [Run](your-wokwi-link) |
| 2 | Gesture-Controlled LED Strip | Control LEDs with hand gestures | [View](project2-gesture-led/sketch.ino) | [Run](your-wokwi-link) |

---

## 🛠️ Skills Learned

### Fundamentals
- ✅ GPIO Input/Output (`pinMode`, `digitalRead`, `digitalWrite`)
- ✅ Pull-up resistors (`INPUT_PULLUP`)
- ✅ Serial Communication (`Serial.begin`, `Serial.print`, `Serial.readString`)
- ✅ Analog Input (`analogRead`)
- ✅ PWM Output (`analogWrite`, `ledcWrite`)

### Displays
- ✅ I2C LCD (16x2)
- ✅ 7-Segment Display (TM1637)
- ✅ Multiple Displays on same I2C bus

### Advanced Concepts
- ✅ Interrupts (`attachInterrupt`, `ISR`)
- ✅ Hardware Timers (`timerBegin`, `timerAttachInterrupt`)
- ✅ Non-blocking timing (`millis()`)
- ✅ PWM Frequency & Resolution

### Connectivity
- ✅ Wi-Fi Connection (`WiFi.begin`)
- ✅ HTTP GET/POST Requests (`HTTPClient`)
- ✅ MQTT Protocol (`PubSubClient`)
- ✅ Cloud Dashboard (ThingsBoard)

### Programming Concepts
- ✅ Arrays and For Loops
- ✅ State Machine Design
- ✅ String Parsing (`.trim`, `.toUpperCase`)
- ✅ Sensor Libraries (`DHT.h`)

---

## 📁 Repository Structure


---

## 🔌 Technologies Used

| Technology | Purpose |
|------------|---------|
| **Arduino Framework** | Embedded programming language |
| **ESP32** | Microcontroller (simulated on Wokwi) |
| **Wokwi** | Online simulator for ESP32 |
| **GitHub** | Version control and portfolio |
| **ThingsBoard** | IoT cloud platform |
| **MQTT** | IoT communication protocol |
| **HTTP** | Web communication protocol |

---

## 📚 Libraries Used

| Library | Purpose |
|---------|---------|
| `DHT.h` | Read temperature/humidity |
| `LiquidCrystal_I2C.h` | Control I2C LCD |
| `TM1637Display.h` | Control 7-segment display |
| `WiFi.h` | Wi-Fi connectivity |
| `HTTPClient.h` | HTTP requests |
| `PubSubClient.h` | MQTT communication |
| `ThingsBoard.h` | ThingsBoard cloud integration |
| `Adafruit_APDS9960.h` | Gesture sensor |

---

## 💡 Key Insights from My Journey

### 1. Interrupts vs Polling
Interrupts allow ESP32 to respond instantly to events, even while sleeping or executing other tasks. This is critical for real-time systems.

### 2. Timers vs Delay
Hardware timers provide precise scheduling without blocking code execution. Multiple timers can run independently.

### 3. MQTT vs HTTP
MQTT is better for IoT because it has:
- Lower bandwidth usage
- Push-based communication
- Built-in one-to-many messaging
- Better battery efficiency

### 4. I2C Protocol
I2C allows multiple devices to share the same 2 pins (SDA, SCL). Each device has its own unique address.

### 5. PWM Frequency
Higher frequency = smoother dimming. 5kHz is ideal for LEDs. Lower frequencies create visible flicker.

---


##  Acknowledgments

- **Wokwi** for their amazing ESP32 simulator
- **ThingsBoard** for their free IoT cloud platform
- **EMQX** for public MQTT broker
- **Open-Meteo** for free weather API

---

## 📱 Connect with Me

- **GitHub:** [Anushka2006-maker](https://github.com/Anushka2006-maker)
- **LinkedIn:** www.linkedin.com/in/anushka-dubey-69409a324

---

## 📅 Timeline

| Period | Activity |
|--------|----------|
| Summer Break | 35-day learning journey |
| Weeks 1-2 | Fundamentals (LEDs, buttons, sensors) |
| Weeks 3-4 | Advanced concepts (interrupts, timers, displays) |
| Week 5 | IoT + Cloud (Wi-Fi, HTTP, MQTT, ThingsBoard) |
| Ongoing | Projects and documentation |

---

## 🏆 Key Achievements

- ✅ Completed 15 learning modules
- ✅ Built 2 portfolio projects
- ✅ Learned 10+ embedded concepts
- ✅ Mastered IoT communication protocols
- ✅ Integrated with cloud platforms

---

*Last Updated: 05 July 2026*

---

**Author:** Anushka  
**Branch:** ECE (Electronics and Communication Engineering)  
**Focus:** IoT and Embedded Systems
