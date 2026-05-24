// PROJECT 2: Gesture-Controlled LED Strip
// Wave your hand to control colors, brightness, and patterns!

#include <Wire.h>
#include <Adafruit_APDS9960.h>

// ============ PIN DEFINITIONS ============
const int LED_PINS[] = {13, 12, 14, 27, 26};
const int NUM_LEDS = 5;

// ============ PWM CHANNELS ============
const int PWM_CHANNELS[] = {0, 1, 2, 3, 4};

// ============ GESTURE SENSOR ============
Adafruit_APDS9960 apds;

// ============ GLOBAL VARIABLES ============
// Current settings
int currentBrightness = 128;      // 0-255
int currentColor[3] = {255, 0, 0}; // RGB values (start with RED)
int currentPattern = 0;            // 0=chaser, 1=blink, 2=rainbow, 3=solid

// Pattern timing
unsigned long lastPatternUpdate = 0;
int patternStep = 0;
int rainbowHue = 0;

// Gesture debounce
unsigned long lastGestureTime = 0;
const int GESTURE_DELAY = 500;     // Wait 500ms between gestures

// ============ COLOR PRESETS ============
const int COLORS[6][3] = {
  {255, 0, 0},     // 0: RED
  {0, 255, 0},     // 1: GREEN
  {0, 0, 255},     // 2: BLUE
  {255, 255, 0},   // 3: YELLOW
  {255, 0, 255},   // 4: MAGENTA
  {255, 255, 255}  // 5: WHITE
};
int colorIndex = 0;

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("========================================");
  Serial.println("   🖐️ GESTURE-CONTROLLED LED STRIP 🖐️");
  Serial.println("========================================");
  Serial.println();
  Serial.println("HOW TO USE:");
  Serial.println("  👆 Wave UP     → Increase brightness");
  Serial.println("  👇 Wave DOWN   → Decrease brightness");
  Serial.println("  👈 Swipe LEFT  → Change pattern");
  Serial.println("  👉 Swipe RIGHT → Change color");
  Serial.println("  🖐️ Proximity   → LED lights up near sensor");
  Serial.println();
  Serial.println("Try waving your hand over the sensor!");
  Serial.println("========================================");
  
  // Initialize gesture sensor
  if (!apds.begin()) {
    Serial.println("❌ APDS9960 sensor not found!");
    Serial.println("Check wiring or restart simulation");
    while (1);
  }
  
  apds.enableProximity(true);
  apds.enableGesture(true);
  
  Serial.println("✅ Gesture sensor ready!");
  
  // Setup PWM for all LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    ledcSetup(PWM_CHANNELS[i], 5000, 8);
    ledcAttachPin(LED_PINS[i], PWM_CHANNELS[i]);
  }
  
  // Initial settings
  setAllLEDs(0, 0, 0);  // Start OFF
  Serial.println("✅ LED strip ready!");
  Serial.println();
}

// ============ MAIN LOOP ============
void loop() {
  // 1. Check for gestures
  handleGestures();
  
  // 2. Check proximity (LED lights up when hand is near)
  handleProximity();
  
  // 3. Update LED pattern based on current mode
  updateLEDPattern();
  
  delay(20);  // Small delay for stability
}

// ============ GESTURE HANDLING ============
void handleGestures() {
  if (!apds.gestureAvailable()) return;
  
  // Debounce gestures
  if (millis() - lastGestureTime < GESTURE_DELAY) return;
  
  uint8_t gesture = apds.readGesture();
  
  switch (gesture) {
    case APDS9960_UP:
      Serial.println("👆 GESTURE: UP - Increasing brightness");
      currentBrightness += 32;
      if (currentBrightness > 255) currentBrightness = 255;
      Serial.print("   Brightness: ");
      Serial.println((currentBrightness * 100) / 255);
      Serial.println("   %");
      lastGestureTime = millis();
      break;
      
    case APDS9960_DOWN:
      Serial.println("👇 GESTURE: DOWN - Decreasing brightness");
      currentBrightness -= 32;
      if (currentBrightness < 0) currentBrightness = 0;
      Serial.print("   Brightness: ");
      Serial.println((currentBrightness * 100) / 255);
      Serial.println("   %");
      lastGestureTime = millis();
      break;
      
    case APDS9960_LEFT:
      Serial.println("👈 GESTURE: LEFT - Changing pattern");
      currentPattern = (currentPattern + 1) % 4;
      Serial.print("   Pattern: ");
      switch(currentPattern) {
        case 0: Serial.println("CHASER"); break;
        case 1: Serial.println("BLINK"); break;
        case 2: Serial.println("RAINBOW"); break;
        case 3: Serial.println("SOLID"); break;
      }
      patternStep = 0;  // Reset pattern position
      lastGestureTime = millis();
      break;
      
    case APDS9960_RIGHT:
      Serial.println("👉 GESTURE: RIGHT - Changing color");
      colorIndex = (colorIndex + 1) % 6;
      currentColor[0] = COLORS[colorIndex][0];
      currentColor[1] = COLORS[colorIndex][1];
      currentColor[2] = COLORS[colorIndex][2];
      Serial.print("   Color: ");
      if (colorIndex == 0) Serial.println("RED");
      else if (colorIndex == 1) Serial.println("GREEN");
      else if (colorIndex == 2) Serial.println("BLUE");
      else if (colorIndex == 3) Serial.println("YELLOW");
      else if (colorIndex == 4) Serial.println("MAGENTA");
      else Serial.println("WHITE");
      lastGestureTime = millis();
      break;
      
    default:
      break;
  }
}

// ============ PROXIMITY HANDLING ============
void handleProximity() {
  int proximity = apds.readProximity();
  
  // Map proximity (0-255) to LED brightness
  // Higher proximity = hand closer = LEDs brighter
  int proximityBrightness = map(proximity, 0, 200, 0, currentBrightness);
  
  // Only show proximity effect if not in a pattern that controls LEDs
  if (currentPattern == 3) {  // SOLID mode
    // Override brightness with proximity
    setAllLEDs(currentColor[0], currentColor[1], currentColor[2]);
    
    // Adjust brightness based on proximity
    for (int i = 0; i < NUM_LEDS; i++) {
      ledcWrite(PWM_CHANNELS[i], proximityBrightness);
    }
  }
  
  // Print proximity when hand is close (for debugging)
  if (proximity > 50) {
    static int lastPrint = 0;
    if (millis() - lastPrint > 500) {
      lastPrint = millis();
      Serial.print("🖐️ Proximity: ");
      Serial.print(proximity);
      Serial.print(" → LED brightness: ");
      Serial.println((proximityBrightness * 100) / 255);
    }
  }
}

// ============ LED PATTERN UPDATES ============
void updateLEDPattern() {
  unsigned long now = millis();
  int delayTime = 100;  // Default pattern speed
  
  switch (currentPattern) {
    case 0:  // CHASER PATTERN (Knight Rider)
      if (now - lastPatternUpdate > 80) {
        lastPatternUpdate = now;
        
        // Turn all LEDs OFF first
        for (int i = 0; i < NUM_LEDS; i++) {
          ledcWrite(PWM_CHANNELS[i], 0);
        }
        
        // Turn on current LED with current color and brightness
        int brightnessValue = map(currentBrightness, 0, 255, 0, 255);
        ledcWrite(PWM_CHANNELS[patternStep], brightnessValue);
        
        patternStep++;
        if (patternStep >= NUM_LEDS) patternStep = 0;
      }
      break;
      
    case 1:  // BLINK PATTERN
      if (now - lastPatternUpdate > 500) {
        lastPatternUpdate = now;
        
        if (patternStep == 0) {
          // All ON
          for (int i = 0; i < NUM_LEDS; i++) {
            int brightnessValue = map(currentBrightness, 0, 255, 0, 255);
            ledcWrite(PWM_CHANNELS[i], brightnessValue);
          }
          patternStep = 1;
        } else {
          // All OFF
          for (int i = 0; i < NUM_LEDS; i++) {
            ledcWrite(PWM_CHANNELS[i], 0);
          }
          patternStep = 0;
        }
      }
      break;
      
    case 2:  // RAINBOW PATTERN
      if (now - lastPatternUpdate > 30) {
        lastPatternUpdate = now;
        
        // Cycle through rainbow colors
        rainbowHue = (rainbowHue + 5) % 360;
        
        // Convert HSV to RGB (simplified rainbow)
        int r, g, b;
        if (rainbowHue < 60) {
          r = 255;
          g = map(rainbowHue, 0, 60, 0, 255);
          b = 0;
        } else if (rainbowHue < 120) {
          r = map(rainbowHue, 60, 120, 255, 0);
          g = 255;
          b = 0;
        } else if (rainbowHue < 180) {
          r = 0;
          g = 255;
          b = map(rainbowHue, 120, 180, 0, 255);
        } else if (rainbowHue < 240) {
          r = 0;
          g = map(rainbowHue, 180, 240, 255, 0);
          b = 255;
        } else if (rainbowHue < 300) {
          r = map(rainbowHue, 240, 300, 0, 255);
          g = 0;
          b = 255;
        } else {
          r = 255;
          g = 0;
          b = map(rainbowHue, 300, 360, 255, 0);
        }
        
        // Apply brightness
        int brightnessFactor = currentBrightness / 255.0;
        r = r * brightnessFactor;
        g = g * brightnessFactor;
        b = b * brightnessFactor;
        
        setAllLEDs(r, g, b);
      }
      break;
      
    case 3:  // SOLID PATTERN - Uses currentColor (already set in main loop)
      // Solid color is handled by proximity function
      break;
  }
}

// ============ HELPER FUNCTIONS ============
void setAllLEDs(int r, int g, int b) {
  // This is for RGB LEDs (if using RGB strip)
  // For now, we'll use brightness for single-color LEDs
  // Each LED gets the same brightness value based on color intensity
  
  int brightnessValue = (r + g + b) / 3;  // Average of RGB
  brightnessValue = map(brightnessValue, 0, 255, 0, currentBrightness);
  
  for (int i = 0; i < NUM_LEDS; i++) {
    ledcWrite(PWM_CHANNELS[i], brightnessValue);
  }
}

void setLEDColor(int ledIndex, int r, int g, int b) {
  // For single-color LEDs, use average brightness
  int brightnessValue = (r + g + b) / 3;
  brightnessValue = map(brightnessValue, 0, 255, 0, currentBrightness);
  ledcWrite(PWM_CHANNELS[ledIndex], brightnessValue);
}
