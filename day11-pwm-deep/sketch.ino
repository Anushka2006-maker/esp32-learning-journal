// Day 11: PWM Deep Dive with LEDC

// ============ PIN DEFINITIONS ============
const int LED1_PIN = 2;   // GPIO2
const int LED2_PIN = 4;   // GPIO4
const int POT_PIN = 34;   // Potentiometer

// ============ PWM CONFIGURATION ============
// LEDC channels (0-15 available on ESP32)
const int LEDC_CHANNEL_1 = 0;
const int LEDC_CHANNEL_2 = 1;

// PWM frequency (Hz)
// Lower = visible flicker, Higher = smoother but less resolution
const int PWM_FREQ = 5000;  // 5kHz - good for LED

// PWM resolution (bits)
// 8 bits = 0-255 brightness levels
const int PWM_RESOLUTION = 8;  // 8-bit resolution (256 steps)

void setup() {
  Serial.begin(115200);
  delay(100);
  
  // ============ SETUP PWM LEDC ============
  // Configure LEDC channels
  ledcSetup(LEDC_CHANNEL_1, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(LEDC_CHANNEL_2, PWM_FREQ, PWM_RESOLUTION);
  
  // Attach channels to GPIO pins
  ledcAttachPin(LED1_PIN, LEDC_CHANNEL_1);
  ledcAttachPin(LED2_PIN, LEDC_CHANNEL_2);
  
  Serial.println("=== PWM DEEP DIVE ===");
  Serial.print("Frequency: ");
  Serial.print(PWM_FREQ);
  Serial.println(" Hz");
  Serial.print("Resolution: ");
  Serial.print(PWM_RESOLUTION);
  Serial.println(" bits (0-255)");
  Serial.println("====================");
  Serial.println();
  Serial.println("LED1: Sweeping brightness (0→255→0)");
  Serial.println("LED2: Control with potentiometer");
  Serial.println();
}

void loop() {
  // ============ LED 1: SMOOTH BRIGHTNESS SWEEP ============
  for (int brightness = 0; brightness <= 255; brightness++) {
    ledcWrite(LEDC_CHANNEL_1, brightness);
    delay(5);
  }
  
  for (int brightness = 255; brightness >= 0; brightness--) {
    ledcWrite(LEDC_CHANNEL_1, brightness);
    delay(5);
  }
  
  // ============ LED 2: POTENTIOMETER CONTROL ============
  int potValue = analogRead(POT_PIN);           // 0-4095
  int brightness = map(potValue, 0, 4095, 0, 255);  // Convert to 0-255
  
  ledcWrite(LEDC_CHANNEL_2, brightness);
  
  // Print PWM info every 100 loops (to avoid spam)
  static int counter = 0;
  counter++;
  if (counter >= 100) {
    counter = 0;
    Serial.print("Potentiometer: ");
    Serial.print(potValue);
    Serial.print(" → Brightness: ");
    Serial.print(brightness);
    Serial.print(" (");
    Serial.print((brightness * 100) / 255);
    Serial.println("%)");
  }
  
  delay(10);
}
