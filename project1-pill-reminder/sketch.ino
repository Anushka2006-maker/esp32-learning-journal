// PROJECT 1: Smart Pill Reminder Box
// Features: Set alarm time, visual alerts, buzzer, acknowledgment button

// ============ PIN DEFINITIONS ============
const int GREEN_LED = 13;    // Ready/Medicine taken
const int YELLOW_LED = 12;   // Warning (time approaching)
const int RED_LED = 14;      // Escalation (missed dose)
const int ACK_BUTTON = 27;   // Acknowledge button
const int BUZZER = 26;       // Piezo buzzer

// ============ VARIABLES ============
int alarmHour = -1;      // Alarm hour (0-23), -1 means no alarm set
int alarmMinute = -1;    // Alarm minute (0-59)

bool alarmTriggered = false;    // Is alarm currently ringing?
bool doseTaken = false;          // Was medicine taken for current alarm?
unsigned long alarmStartTime = 0; // When alarm started ringing

// For simulation time tracking
unsigned long lastSecond = 0;
int simulatedHour = 12;    // Start at 12:00 PM
int simulatedMinute = 0;

// Escalation stages
int escalationLevel = 0;    // 0=none, 1=first warning, 2=escalated

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  delay(100);
  
  // Configure pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(ACK_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  
  // Initial LED states
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  
  // Welcome message
  Serial.println("========================================");
  Serial.println(" SMART PILL REMINDER BOX ");
  Serial.println("========================================");
  Serial.println();
  Serial.println("COMMANDS:");
  Serial.println("  SET HH:MM  - Set alarm (24-hour format)");
  Serial.println("  STATUS     - Check current alarm time");
  Serial.println("  CANCEL     - Cancel current alarm");
  Serial.println("  HELP       - Show this menu");
  Serial.println();
  Serial.println("EXAMPLE: SET 14:30 (alarm at 2:30 PM)");
  Serial.println("========================================");
}

// ============ MAIN LOOP ============
void loop() {
  // 1. Handle Serial Commands
  handleSerialCommands();
  
  // 2. Update simulated time (1 real second = 1 minute in simulation)
  updateSimulatedTime();
  
  // 3. Check if alarm should trigger
  checkAlarm();
  
  // 4. Handle active alarm
  if (alarmTriggered && !doseTaken) {
    handleActiveAlarm();
  }
  
  // 5. Check acknowledgment button
  checkAcknowledgeButton();
  
  // 6. Update status LED based on time remaining
  updateStatusLED();
  
  delay(100);  // Small delay for stability
}

// ============ UPDATE SIMULATED TIME ============
void updateSimulatedTime() {
  unsigned long currentMillis = millis();
  
  // Every 1000ms (1 real second), advance time by 1 minute
  if (currentMillis - lastSecond >= 1000) {
    lastSecond = currentMillis;
    
    simulatedMinute++;
    if (simulatedMinute >= 60) {
      simulatedMinute = 0;
      simulatedHour++;
      if (simulatedHour >= 24) {
        simulatedHour = 0;
      }
    }
    
    // Print time every 15 minutes (for demo)
    if (simulatedMinute % 15 == 0) {
      printCurrentTime();
      
      // If alarm is set, show time remaining
      if (alarmHour != -1) {
        int minutesLeft = calculateMinutesLeft();
        if (minutesLeft >= 0) {
          Serial.print("    Alarm in ");
          Serial.print(minutesLeft);
          Serial.println(" minutes");
        }
      }
    }
  }
}

// ============ PRINT CURRENT TIME ============
void printCurrentTime() {
  Serial.print(" Current time: ");
  Serial.print(simulatedHour);
  Serial.print(":");
  if (simulatedMinute < 10) Serial.print("0");
  Serial.print(simulatedMinute);
  Serial.print(" ");
  if (simulatedHour < 12) {
    Serial.println("AM");
  } else {
    Serial.println("PM");
  }
}

// ============ CALCULATE MINUTES UNTIL ALARM ============
int calculateMinutesLeft() {
  if (alarmHour == -1) return -1;
  
  int currentTotal = simulatedHour * 60 + simulatedMinute;
  int alarmTotal = alarmHour * 60 + alarmMinute;
  
  if (alarmTotal > currentTotal) {
    return alarmTotal - currentTotal;
  } else {
    // Alarm for tomorrow
    return (24*60 - currentTotal) + alarmTotal;
  }
}

// ============ CHECK IF ALARM SHOULD TRIGGER ============
void checkAlarm() {
  if (alarmHour == -1) return;           // No alarm set
  if (alarmTriggered) return;            // Already triggered
  if (doseTaken) return;                 // Already taken
  
  int currentTotal = simulatedHour * 60 + simulatedMinute;
  int alarmTotal = alarmHour * 60 + alarmMinute;
  
  if (currentTotal == alarmTotal) {
    triggerAlarm();
  }
}

// ============ TRIGGER THE ALARM ============
void triggerAlarm() {
  alarmTriggered = true;
  alarmStartTime = millis();
  escalationLevel = 0;
  
  Serial.println();
  Serial.println("🔔");
  Serial.println(" TIME TO TAKE YOUR MEDICINE! ");
  Serial.println("🔔");
  Serial.println();
  Serial.println(" Press the ACKNOWLEDGE BUTTON after taking your medicine");
  Serial.println();
  
  digitalWrite(GREEN_LED, HIGH);
}

// ============ HANDLE ACTIVE ALARM (Buzzer + Escalation) ============
void handleActiveAlarm() {
  unsigned long elapsedTime = (millis() - alarmStartTime) / 1000; // seconds elapsed
  
  // Check for escalation (5 minutes = 300 seconds simulated)
  if (elapsedTime >= 300 && escalationLevel == 0) {
    escalationLevel = 1;
    Serial.println();
    Serial.println(" WARNING: Medicine not taken yet! ");
    Serial.println("Please take your medicine and press the button!");
    Serial.println();
  }
  
  // Check for second escalation (8 minutes)
  if (elapsedTime >= 480 && escalationLevel == 1) {
    escalationLevel = 2;
    digitalWrite(YELLOW_LED, HIGH);
    Serial.println();
    Serial.println(" ESCALATION: MISSED DOSE ALERT! ");
    Serial.println(" Contact caregiver or check medicine box!");
    Serial.println();
  }
  
  // Buzzer pattern based on escalation level
  if (escalationLevel == 0) {
    // Normal: Beep every 2 seconds
    if ((millis() / 1000) % 2 == 0) {
      tone(BUZZER, 1000);
    } else {
      noTone(BUZZER);
    }
  } else if (escalationLevel == 1) {
    // Warning: Beep every 1 second (faster)
    if ((millis() / 500) % 2 == 0) {
      tone(BUZZER, 2000);
    } else {
      noTone(BUZZER);
    }
  } else {
    // Escalated: Continuous fast beep
    tone(BUZZER, 2500);
  }
  
  // Red LED for escalated mode
  if (escalationLevel >= 2) {
    digitalWrite(RED_LED, HIGH);
  }
}

// ============ CHECK ACKNOWLEDGE BUTTON ============
void checkAcknowledgeButton() {
  if (digitalRead(ACK_BUTTON) == LOW) {
    delay(50);  // Debounce
    
    if (digitalRead(ACK_BUTTON) == LOW) {
      if (alarmTriggered && !doseTaken) {
        // Medicine taken!
        doseTaken = true;
        alarmTriggered = false;
        noTone(BUZZER);
        
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, LOW);
        
        Serial.println();
        Serial.println(" MEDICINE TAKEN! ");
        Serial.println(" Good job! Next reminder in 12 hours.");
        Serial.println();
        
        // Auto-set next alarm in 12 hours
        int nextHour = alarmHour + 12;
        if (nextHour >= 24) nextHour -= 24;
        alarmHour = nextHour;
        // Keep same minute
        doseTaken = false;
        alarmTriggered = false;
        escalationLevel = 0;
        
        Serial.print("🆕 Next alarm set for: ");
        Serial.print(alarmHour);
        Serial.print(":");
        if (alarmMinute < 10) Serial.print("0");
        Serial.println(alarmMinute);
        
      } else if (!alarmTriggered) {
        Serial.println("ℹ️ Button pressed, but no active alarm.");
      }
      
      // Wait for button release
      while(digitalRead(ACK_BUTTON) == LOW) {
        delay(10);
      }
    }
  }
}

// ============ UPDATE STATUS LED BASED ON TIME REMAINING ============
void updateStatusLED() {
  if (alarmHour == -1) {
    // No alarm set - all LEDs off
    digitalWrite(YELLOW_LED, LOW);
    return;
  }
  
  if (alarmTriggered || doseTaken) return;
  
  int minutesLeft = calculateMinutesLeft();
  
  if (minutesLeft <= 5 && minutesLeft > 0) {
    // 5 minutes before: Fast blink yellow
    if ((millis() / 300) % 2 == 0) {
      digitalWrite(YELLOW_LED, HIGH);
    } else {
      digitalWrite(YELLOW_LED, LOW);
    }
  } else if (minutesLeft <= 15 && minutesLeft > 5) {
    // 15 minutes before: Slow blink yellow
    if ((millis() / 800) % 2 == 0) {
      digitalWrite(YELLOW_LED, HIGH);
    } else {
      digitalWrite(YELLOW_LED, LOW);
    }
  } else if (minutesLeft <= 30 && minutesLeft > 15) {
    // 30 minutes before: Solid yellow
    digitalWrite(YELLOW_LED, HIGH);
  } else {
    digitalWrite(YELLOW_LED, LOW);
  }
}

// ============ HANDLE SERIAL COMMANDS ============
void handleSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readString();
    command.trim();
    command.toUpperCase();
    
    if (command.startsWith("SET")) {
      // Parse "SET HH:MM"
      int spaceIndex = command.indexOf(' ');
      if (spaceIndex > 0) {
        String timeStr = command.substring(spaceIndex + 1);
        int colonIndex = timeStr.indexOf(':');
        
        if (colonIndex > 0) {
          int hour = timeStr.substring(0, colonIndex).toInt();
          int minute = timeStr.substring(colonIndex + 1).toInt();
          
          if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
            alarmHour = hour;
            alarmMinute = minute;
            alarmTriggered = false;
            doseTaken = false;
            escalationLevel = 0;
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(RED_LED, LOW);
            noTone(BUZZER);
            
            Serial.println();
            Serial.print("✅ Alarm set for ");
            Serial.print(alarmHour);
            Serial.print(":");
            if (alarmMinute < 10) Serial.print("0");
            Serial.print(alarmMinute);
            Serial.println();
            
            int minutesLeft = calculateMinutesLeft();
            if (minutesLeft >= 0) {
              Serial.print("⏰ Alarm will ring in ");
              Serial.print(minutesLeft);
              Serial.println(" minutes");
            }
            Serial.println();
          } else {
            Serial.println(" Invalid time! Use 00:00 to 23:59");
          }
        } else {
          Serial.println("Use format: SET HH:MM (example: SET 14:30)");
        }
      }
    }
    else if (command == "STATUS") {
      Serial.println();
      if (alarmHour == -1) {
        Serial.println("📋 No alarm currently set");
      } else {
        Serial.print("📋 Alarm set for ");
        Serial.print(alarmHour);
        Serial.print(":");
        if (alarmMinute < 10) Serial.print("0");
        Serial.println(alarmMinute);
        
        int minutesLeft = calculateMinutesLeft();
        if (minutesLeft >= 0) {
          Serial.print("⏰ Time remaining: ");
          Serial.print(minutesLeft);
          Serial.println(" minutes");
        }
      }
      Serial.println();
    }
    else if (command == "CANCEL") {
      alarmHour = -1;
      alarmMinute = -1;
      alarmTriggered = false;
      doseTaken = false;
      escalationLevel = 0;
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(RED_LED, LOW);
      noTone(BUZZER);
      Serial.println(" Alarm cancelled");
      Serial.println();
    }
    else if (command == "HELP") {
      Serial.println();
      Serial.println(" SMART PILL REMINDER - COMMANDS:");
      Serial.println("  SET HH:MM  - Set alarm (24-hour format)");
      Serial.println("  STATUS     - Check alarm status");
      Serial.println("  CANCEL     - Cancel current alarm");
      Serial.println("  HELP       - Show this menu");
      Serial.println();
    }
    else {
      // Ignore empty or unknown commands
      if (command.length() > 0) {
        Serial.print(" Unknown: ");
        Serial.println(command);
        Serial.println("Type HELP for available commands");
      }
    }
  }
}
