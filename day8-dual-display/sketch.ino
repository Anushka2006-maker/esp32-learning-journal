// Day 8: Multiple Displays - LCD + 7-Segment
// Shows same data on both displays simultaneously

#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>

// ============ LCD SETUP ============
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27, 16x2 LCD

// ============ 7-SEGMENT SETUP ============
// TM1637 pins connected to ESP32
#define CLK_PIN 21   // Same as SDA? Yes! They share
#define DIO_PIN 22   // Same as SCL? Yes! They share

TM1637Display display(CLK_PIN, DIO_PIN);

// ============ VARIABLES ============
int counter = 0;
unsigned long lastUpdate = 0;
const int POT_PIN = 34;

void setup() {
  Serial.begin(115200);
  
  // ============ INITIALIZE LCD ============
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // ============ INITIALIZE 7-SEGMENT ============
  display.setBrightness(7);  // Brightness 0-7 (7 = brightest)
  display.clear();
  
  // Show startup message
  lcd.setCursor(0, 0);
  lcd.print("Dual Display Demo");
  lcd.setCursor(0, 1);
  lcd.print("LCD + 7-Segment");
  
  display.showNumberDec(8888);  // Test pattern: all segments ON
  delay(2000);
  
  lcd.clear();
  display.clear();
  
  Serial.println("=== Dual Display Ready ===");
  Serial.println("Counter will increment every second");
  Serial.println("Turn potentiometer to change counter");
}

void loop() {
  // Read potentiometer value (0-4095) and map to 0-9999
  int potValue = analogRead(POT_PIN);
  int displayValue = map(potValue, 0, 4095, 0, 9999);
  
  // Update displays every 100ms (smooth potentiometer reading)
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();
    
    // ============ UPDATE LCD ============
    lcd.setCursor(0, 0);
    lcd.print("Value: ");
    lcd.print(displayValue);
    lcd.print("    ");  // Spaces to clear old digits
    
    // Show potentiometer as bar graph on LCD row 2
    lcd.setCursor(0, 1);
    lcd.print("|");
    int barLength = map(displayValue, 0, 9999, 0, 14);
    for (int i = 0; i < barLength; i++) {
      lcd.print("=");
    }
    for (int i = barLength; i < 14; i++) {
      lcd.print(" ");
    }
    lcd.print("|");
    
    // ============ UPDATE 7-SEGMENT ============
    display.showNumberDec(displayValue);
    
    // Optional: Show with leading zeros (e.g., 0042)
    // display.showNumberDecEx(displayValue, 0b11100000, false);
    
    Serial.print("Potentiometer: ");
    Serial.print(potValue);
    Serial.print(" → Display: ");
    Serial.println(displayValue);
  }
}
