// Day 5: Control LED using Serial Commands

const int LED_PIN = 2;
String receivedCommand = "";  // Store incoming command

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Start with LED OFF
  
  Serial.println("=== LED Controller ===");
  Serial.println("Commands you can send:");
  Serial.println("  ON  - Turn LED ON");
  Serial.println("  OFF - Turn LED OFF");
  Serial.println("  BLINK - LED blinks 3 times");
  Serial.println("  HELP - Show this menu");
  Serial.println("=========================");
}

void loop() {
  // Check if any data is available from Serial Monitor
  if (Serial.available() > 0) {
    
    // Read the incoming command as a string
    receivedCommand = Serial.readString();
    
    // Remove any extra spaces or newline characters
    receivedCommand.trim();
    
    // Convert to uppercase for easier comparison
    receivedCommand.toUpperCase();
    
    // Check which command was sent
    if (receivedCommand == "ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("✅ LED turned ON");
    }
    else if (receivedCommand == "OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("✅ LED turned OFF");
    }
    else if (receivedCommand == "BLINK") {
      Serial.println("💡 LED blinking 3 times...");
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(300);
        digitalWrite(LED_PIN, LOW);
        delay(300);
      }
      Serial.println("✅ Blinking complete!");
    }
    else if (receivedCommand == "HELP") {
      Serial.println("--- Available Commands ---");
      Serial.println("ON    - Turn LED ON");
      Serial.println("OFF   - Turn LED OFF");
      Serial.println("BLINK - LED blinks 3 times");
      Serial.println("HELP  - Show this menu");
      Serial.println("--------------------------");
    }
    else {
      Serial.print("❌ Unknown command: ");
      Serial.print(receivedCommand);
      Serial.println(". Type HELP for available commands.");
    }
  }
  
  // No delay needed - keeps listening continuously
}
