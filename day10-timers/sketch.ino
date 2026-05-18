// Day 10: Hardware Timers - Precise Scheduling

// ESP32 has 4 hardware timers (0, 1, 2, 3)
// We'll use Timer 0

// Timer variables
hw_timer_t* timer = NULL;
volatile bool timerFlag = false;
volatile int timerCount = 0;

// LED pins
const int LED1_PIN = 2;
const int LED2_PIN = 4;

// ============ TIMER INTERRUPT FUNCTION ============
// This runs automatically every time timer triggers
void IRAM_ATTR onTimer() {
  // This is an ISR - keep it VERY short!
  timerFlag = true;
  timerCount++;
}

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  // Configure Timer 0
  timer = timerBegin(0, 80, true);
  // timerBegin(timer number, prescaler, count up)
  // Prescaler 80 = 1 microsecond per count (80MHz / 80 = 1MHz)
  
  // Attach interrupt
  timerAttachInterrupt(timer, &onTimer, true);
  
  // Set timer to trigger every 1,000,000 microseconds = 1 second
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
  
  Serial.println("=== Hardware Timer Demo ===");
  Serial.println("Timer triggers every 1 second");
  Serial.println("LED1: Blinking using delay() (BLOCKS)");
  Serial.println("LED2: Blinking using timer (NON-BLOCKING)");
  Serial.println("Watch the difference!");
  Serial.println("===========================");
}

// ============ MAIN LOOP ============
void loop() {
  // ===== LED 1: OLD WAY (uses delay - BLOCKS) =====
  digitalWrite(LED1_PIN, HIGH);
  delay(500);              // FREEZES for 500ms!
  digitalWrite(LED1_PIN, LOW);
  delay(500);              // FREEZES again!
  
  // ===== THE PROBLEM: During those delays, nothing else runs!
  // ===== But timer INTERRUPT still works because it's HARDWARE!
  
  // Check timer flag (set by interrupt)
  if (timerFlag) {
    timerFlag = false;
    
    // This runs EXACTLY every 1 second, even during delays!
    Serial.print("Timer triggered! Count: ");
    Serial.println(timerCount);
    
    // LED 2: Toggle using timer (doesn't block main loop)
    static bool led2State = false;
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State);
  }
}
