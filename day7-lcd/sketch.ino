/ Day 7: LCD Display - Hello World

#include <LiquidCrystal_I2C.h>

// I2C address: 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize LCD
  lcd.init();
  
  // Turn on backlight
  lcd.backlight();
  
  // Clear any existing text
  lcd.clear();
  
  // Print text at row 0, column 0 (first row, first column)
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  
  lcd.setCursor(0, 1);
  lcd.print("ESP32 + LCD");
}

void loop() {
  // Nothing here yet
}
