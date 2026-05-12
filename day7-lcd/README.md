# Day 7: LCD Display (16x2 I2C)

## What I Learned

### New Concepts
- **LCD Display** – 16x2 character screen
- **I2C Protocol** – 2-wire communication (SDA, SCL)
- **LiquidCrystal_I2C library** – LCD control
- **lcd.setCursor()** – Position text
- **lcd.print()** – Display text

### I2C Pins on ESP32
| Pin | Function |
|-----|----------|
| GPIO21 | SDA (Data) |
| GPIO22 | SCL (Clock) |

##Simulation
https://wokwi.com/projects/463821855609066497

## My Code
```cpp
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print("ESP32 + LCD");
}

void loop() {
  // Nothing yet
}
