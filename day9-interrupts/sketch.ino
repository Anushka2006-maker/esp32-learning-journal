// Day 9: Interrupts - Instant Button Response

const int LED_PIN = 2;
const int BUTTON_PIN = 15;

// volatile tells compiler this variable can change at any time (in interrupt)
volatile bool buttonPressed = false;
int blinkCount = 0;

void IRAM_ATTR buttonISR() {
  // This function runs IMMEDIATELY when button is pressed
  // Keep it VERY short and simple!
  buttonPressed = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Attach interrupt to button pin
  // FALLING = when button goes from HIGH to LOW (pressed)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  
  Serial.println("=== Interrupt Demo ===");
  Serial.println("Main program: LED blinking slowly");
  Serial.println("Press button → Instant response (stops blink, shows count)");
  Serial.println("========================");
}

void loop() {
  // Main program: LED blinks slowly
  // Even while blinking, interrupt can fire instantly!
  
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
  blinkCount++;
  
  // Check if button was pressed (interrupt set this flag)
  if (buttonPressed) {
    buttonPressed = false;  // Reset flag
    
    // Stop blinking briefly to show response
    digitalWrite(LED_PIN, LOW);
    
    Serial.print("🔴 BUTTON PRESSED! (Interrupt triggered)");
    Serial.print(" | Blinks so far: ");
    Serial.println(blinkCount);
    
    // Fast blink to acknowledge
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
    
    Serial.println("Resuming normal blinking...");
    Serial.println();
  }
}
