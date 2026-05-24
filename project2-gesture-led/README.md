# Project 2: Gesture-Controlled LED Strip 

## Project Overview
A virtual LED strip controlled by hand gestures using an APDS9960 gesture sensor. Wave your hand to change colors, brightness, and lighting patterns!

## Features

| Gesture | Action |
|---------|--------|
| 👆 Wave UP | Increase brightness |
| 👇 Wave DOWN | Decrease brightness |
| 👈 Swipe LEFT | Change pattern |
| 👉 Swipe RIGHT | Change color |
| 🖐️ Proximity | LED brightness follows hand distance |

## Patterns Available
- **Chaser** - Knight Rider style (LEDs chase left to right)
- **Blink** - All LEDs blink together
- **Rainbow** - Automatic color cycling
- **Solid** - Single color, proximity-controlled brightness

## Colors Available
- Red → Green → Blue → Yellow → Magenta → White

## Circuit Components

| Component | Pins Used |
|-----------|-----------|
| APDS9960 Gesture Sensor | GPIO21 (SDA), GPIO22 (SCL) |
| 5x LEDs | GPIO13,12,14,27,26 |

## How It Works
1. APDS9960 sensor detects hand gestures
2. ESP32 processes gesture type
3. LED strip updates based on gesture:
   - UP/DOWN → Adjust brightness
   - LEFT/RIGHT → Change color/pattern
   - Proximity → Real-time brightness control

## Technologies Used
- C++ (Arduino framework)
- ESP32 microcontroller
- APDS9960 gesture sensor (I2C)
- PWM (LED brightness control)
- State machine design

## Simulation Link
https://wokwi.com/projects/464911814482180097


## Future Improvements
- Add more patterns (pulse, wave, random sparkle)
- Support for real RGB LED strips
- Gesture customization via Serial commands
- Save preferences to EEPROM

## Author
Anushka - ECE Student

## Date
24-05-2026
